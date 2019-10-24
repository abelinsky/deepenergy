#include "pch.h"
#include "ObjectsModel.h"
#include "Objects.h"
#include "ConnectionsMatrix.h"
#include "Node.h"
#include "FileSystem.h"

namespace Core {

CObjectsModel::CObjectsModel(void)
{
	m_pGTS = NULL;
	m_bSchemeChanged = false;
	m_rEdgesCount = 0;
	m_bFlowMode = false;
	m_nMaxNSIID = 0;
}

CObjectsModel::~CObjectsModel(void)
{
	Clear();
}

void CObjectsModel::Clear()
{
	m_rQtg = 0;
	m_rW = 0;
	m_rN = 0;
	m_rsL = 0;
	m_rsWAVO = 0;
	m_rsQtgCost = 0;
	m_rsWCost = 0;
	m_rsWAVOCost = 0;
	m_rTinDelta = 0;

	m_A_ttr = 0;
	m_A_ettr = 0;
	m_A_ottr = 0;

	m_RestrictionsP = 0;

	for (list <BObject*>::iterator i = m_ObjectsList.begin(); i != m_ObjectsList.end(); i++)
	{
		BObject *pObject = *i;
		delete pObject;
	}
	m_ObjectsList.clear();
	m_Objects.clear();
	m_Connections.Clear();

	for (unordered_map <int, BNSIGPA*>::iterator i = m_NSIGPA.begin(); i != m_NSIGPA.end(); i++)
	{
		BNSI *pNSI = i->second;
		delete pNSI;
	}
	m_NSIGPA.clear();

	for (unordered_map <int, BNSIAVO*>::iterator i = m_NSIAVO.begin(); i != m_NSIAVO.end(); i++)
	{
		BNSI *pNSI = i->second;
		delete pNSI;
	}
	m_NSIAVO.clear();

	m_ParallelShops.clear();

	m_Ins.clear();
	m_Outs.clear();
	m_Pipes.clear();
	m_Losts.clear();
	m_GPAs.clear();
	m_RDValves.clear();
	m_Shops.clear();
	m_Valves.clear();

	// m_ControlParams.clear();
}

void CObjectsModel::AddObject(BObject *pObject)
{
	assert(!m_Objects[pObject->m_ID]);
	m_ObjectsList.push_back(pObject);
	m_Objects[pObject->m_ID] = pObject;
}

void CObjectsModel::EraseObject(BObject *pObject)
{
	list <BObject*>::iterator i = find(m_ObjectsList.begin(), m_ObjectsList.end(), pObject);
	if (i != m_ObjectsList.end())
		m_ObjectsList.erase(i);
	unordered_map <int, BObject*>::iterator j = m_Objects.find(pObject->m_ID);
	if (j != m_Objects.end())
		m_Objects.erase(j);
	pObject->PostErased();
}

BObject* CObjectsModel::GetObject(int ID)
{
	if (m_Objects.find(ID) != m_Objects.end())
		return m_Objects[ID];
	return NULL;
}

bool CObjectsModel::AddNSIGPA(BNSIGPA *pNSI, string& Error)
{
	if (m_NSIGPA.find(pNSI->m_ID) != m_NSIGPA.end())
	{
		string s;
		s = (boost::format("There are several objects NSIGPA with the same ID %d") % pNSI->m_ID).str();
		Error += s;
		return false;
	}
	m_NSIGPA[pNSI->m_ID] = pNSI;
	if (pNSI->m_ID>=m_nMaxNSIID)
	{
		m_nMaxNSIID = pNSI->m_ID+1;
	}
	return true;
}

BNSIGPA* CObjectsModel::GetNSIGPA(int ID)
{
	if (m_NSIGPA.find(ID) != m_NSIGPA.end())
		return m_NSIGPA[ID];
	return NULL;
}

bool CObjectsModel::AddNSIAVO(BNSIAVO *pNSI, string& Error)
{
	if (m_NSIAVO.find(pNSI->m_ID) != m_NSIAVO.end())
	{
		string s;
		s = (boost::format("There are several objects NSIAVO with the same ID %d") % pNSI->m_ID).str();
		Error += s;
		return false;
	}
	m_NSIAVO[pNSI->m_ID] = pNSI;
	return true;
}

BNSIAVO* CObjectsModel::GetNSIAVO(int ID)
{
	if (m_NSIAVO.find(ID) != m_NSIAVO.end())
		return m_NSIAVO[ID];
	return NULL;
}

bool CObjectsModel::LoadData(const string& DataDir, string &Error, string &Warnings)
{
	bool bSuccess = true;

	Clear();

	// Информация по ограничениям ГТС
	
	CFileSystem fs;
	string s;

	string ss = fs.GetCurrentDirectory();


	char fName[256];
	{
		sprintf_s(fName, "%sLimitationsGTS.dat", DataDir.c_str());
		if (!fs.FileExists(fName)) 
		{
			Error = "File not found: LimitationsGTS.dat.";
			return false;
		}
		
		BGTS *pGTS = new BGTS;
		pGTS->m_ID = 0;
		AddObject(pGTS);
		ifstream inGTS(fName);
		pGTS->LoadData(inGTS);
		inGTS.close();
	}

	// Считывание перечня КЦ, заданных как объекты потерь давления
	struct ShopLostData
	{
		int ShopNumber;
		string KSName;
		void operator= (const ShopLostData &SourceData)
		{
			ShopNumber = SourceData.ShopNumber;
			KSName = SourceData.KSName;
		}
	};
	unordered_map<int, int> LostShops;
	unordered_map<int, ShopLostData> LostShopsData;
	{
		sprintf_s(fName, "%sLost_ad.dat", DataDir.c_str());
		if (fs.FileExists(fName)) 
		{
			ifstream inSLost(fName);
			int nSLostCount;
			inSLost >> nSLostCount;
			getline(inSLost, s);
			for (int i = 0; i<nSLostCount; i++)
			{
				ShopLostData SData;
				int ID;
				inSLost >> ID;
				inSLost >> SData.ShopNumber;
				inSLost >> SData.KSName;
				LostShops[ID] = 2; // в матрице связей КЦ представлен с id=2
				LostShopsData[ID] = SData;
				getline(inSLost, s);
			}
			inSLost.close();
		}
	}

	// Информация о расчетной схеме ГТС
	{
		sprintf_s(fName, "%sMatrixConnections.dat", DataDir.c_str());
		if (!fs.FileExists(fName)) 
		{
			Error = "File not found: MatrixConnections.dat.";
			return false;
		}
		ifstream inMatrix(fName);
		if (!m_Connections.LoadData(inMatrix, Error, &LostShops))
			return false;
		inMatrix.close();
	}

	// НСИ по ГПА
	{
		sprintf_s(fName, "%sGpaNsi.dat", DataDir.c_str());
		if (!fs.FileExists(fName))
		{
			Error = "File not found: GpaNsi.dat.";
			return false;
		}
		ifstream inNSIGPA(fName);
		int nNSICount;
		inNSIGPA >> nNSICount;
		getline(inNSIGPA, s);
		for (int i = 0; i<nNSICount; i++)
		{
			BNSIGPA *pNSI = new BNSIGPA;
			pNSI->LoadData(inNSIGPA);
			if (!AddNSIGPA(pNSI, Error))
				return false;
			getline(inNSIGPA, s);
		}
		inNSIGPA.close();
	}

	// НСИ по АВО
	{
		sprintf_s(fName, "%sAirNsi.dat", DataDir.c_str());
		if (!fs.FileExists(fName))
		{
			Error = "File not found: AirNsi.dat.";
			return false;
		}
		ifstream inAVO(fName);
		int nNSIAVOCount;
		inAVO >> nNSIAVOCount;
		getline(inAVO, s);
		for (int i = 0; i<nNSIAVOCount; i++)
		{
			BNSIAVO *pNSI = new BNSIAVO;
			pNSI->LoadData(inAVO);
			AddNSIAVO(pNSI, Warnings);
			getline(inAVO, s);
		}
		inAVO.close();
	}

	// Информация по входам/выходам ГТС и отборам
	{
		sprintf_s(fName, "%sInOutGRS.dat", DataDir.c_str());
		if (!fs.FileExists(fName)) 
		{
			Error = "File not found: InOutGRS.dat.";
			return false;
		}
		ifstream inInOut(fName);
		if (!BInOut::LoadData(inInOut, Error))
			return false;
		inInOut.close();
	}

	// Информация по трубам
	{
		sprintf_s(fName, "%sPipeLine.dat", DataDir.c_str());
		if (!fs.FileExists(fName)) 
		{
			Error = "File not found: PipeLine.dat.";
			return false;
		}
		ifstream inPipes(fName);
		int nPipesCount;
		inPipes >> nPipesCount;
		getline(inPipes, s);
		for (int i = 0; i<nPipesCount; i++)
		{
			int ID;
			inPipes >> ID;
			BPipe *pPipe = dynamic_cast<BPipe*>(GetObject(ID));
			if (!pPipe)
			{
				string warning;
				warning = (boost::format("Object (pipe) was not found: № %d.\n") % ID).str();
				Warnings += warning;
				getline(inPipes, s);
				continue;
			}
			pPipe->LoadData(inPipes);
			getline(inPipes, s);
		}
		inPipes.close();
	}


	// Информация по объектам потерь давления газа (ГИС)
	{
		sprintf_s(fName, "%sLost.dat", DataDir.c_str());
		if (!fs.FileExists(fName))
		{
			Warnings += "File not found: Lost.dat.";			
		}
		else
		{
			ifstream inLost(fName);
			int nLostCount;
			inLost >> nLostCount;
			getline(inLost, s);
			for (int i = 0; i<nLostCount; i++)
			{
				int ID;
				inLost >> ID;
				BObject *pObject = GetObject(ID);
				BObject *pLost = dynamic_cast<BLost*>(pObject);
				if (!pLost)
				{
					BShop *pShop = dynamic_cast<BShop*>(pObject);
					if (pShop)
					{
						pShop->SetFlowMode();
						pShop->m_KSName = LostShopsData[ID].KSName;
						pShop->m_ShopNumber = LostShopsData[ID].ShopNumber;
					}
					pLost = pShop;
				}
				if (!pLost)
				{
					string error;
					error = (boost::format("Object (lost) was not found: № %d.\n") % ID).str();
					Error += error;
					getline(inLost, s);
					bSuccess = false;
					continue;
				}
				pLost->LoadData(inLost);
				getline(inLost, s);
			}
			inLost.close();
		}
	}


	// Информация по кранам
	{
		sprintf_s(fName, "%sCrane.dat", DataDir.c_str());
		if (!fs.FileExists(fName))
		{
			Warnings += "File not found: Crane.dat.";
		}
		else
		{
			ifstream inCrane(fName);
			int nCraneCount;
			inCrane >> nCraneCount;
			getline(inCrane, s);
			for (int i = 0; i<nCraneCount; i++)
			{
				int ID;
				inCrane >> ID;
				BRDValve *pValve = dynamic_cast<BRDValve*>(GetObject(ID));
				if (!pValve)
				{
					string error;
					error = (boost::format("Object (RDValve) was not found: № %d.\n") % ID).str();
					Error += error;
					getline(inCrane, s);
					bSuccess = false;
					continue;
				}
				pValve->LoadData(inCrane);
				getline(inCrane, s);
			}
			inCrane.close();
		}
	}

	// Информация по КЦ
	{
		sprintf_s(fName, "%sCompressorShop.dat", DataDir.c_str());
		if (!fs.FileExists(fName))
		{
			Error = "File not found: CompressorShop.dat.";
			return false;
		}
		ifstream inCShop(fName);
		int nCShopCount;
		inCShop >> nCShopCount;
		getline(inCShop, s);
		for (int i = 0; i<nCShopCount; i++)
		{
			int ID;
			inCShop >> ID;

			BShop *pShop = dynamic_cast<BShop*>(GetObject(ID));
			getline(inCShop, s);

			BShop DumbShop;
			if (!pShop)
			{
				string error;
				error = (boost::format("Object (Shop) was not found: № %d.\n") % ID).str();
				Error += error;
				bSuccess = false;
				
				
				pShop = &DumbShop;

				//continue;
			}		

			pShop->LoadData(inCShop);
			getline(inCShop, s);
		}
		inCShop.close();
	}

	// Проверка корректности исходных данных
	for (list <BObject*>::iterator i = m_ObjectsList.begin(); i != m_ObjectsList.end(); i++)
	{
		BObject *pObject = *i;
		pObject->PostAdd();
		bSuccess &= pObject->CheckLoadedData(Error);
	}
	for (unordered_map <int, BNSIGPA*>::iterator i = m_NSIGPA.begin(); i != m_NSIGPA.end(); i++)
	{
		BNSI *pNSI = i->second;
		bSuccess &= pNSI->CheckLoadedData(Error);
	}
	for (unordered_map <int, BNSIAVO*>::iterator i = m_NSIAVO.begin(); i != m_NSIAVO.end(); i++)
	{
		BNSI *pNSI = i->second;
		bSuccess &= pNSI->CheckLoadedData(Error);
	}

	m_Connections.PostObjectsLoad(); // добавление объектов, контролирующих параллельные КЦ
	
	sort(m_Shops.begin(), m_Shops.end(), BObject::OBJCMP);

	DefineControlParams();

	return bSuccess;
}

bool CObjectsModel::DynPrepare(const string& DataDir)
{
	CFileSystem fs;
	string ss = fs.GetCurrentDirectory();

	char fName[256];
	
	DoLogForced("gData.m_DataDir is: " + gData.m_DataDir);

	sprintf_s(fName, "%sInOutGRSMap.dat", DataDir.c_str());
	m_InOutMap.Open(fName);

	return true;
}

bool CObjectsModel::DynExport(int stratum)
{
	if (!m_InOutMap.IsOpened())
	{
		DoLog("Failed to CObjectsModel::DynExport because m_InOutMap is not opened.");
		return false;
	}

	m_InOutMap.SetPosition(0);
	int stratums_number = 0;
	m_InOutMap >> stratums_number;
	
	int order = 0;
	for (auto pObject : m_Ins) 
	{
		// <test>
		dynamic_cast<BIn*>(pObject)->m_rQ = stratum;
		dynamic_cast<BIn*>(pObject)->m_rP = stratum;
		dynamic_cast<BIn*>(pObject)->m_rT = stratum;
		dynamic_cast<BIn*>(pObject)->m_rRo = stratum;
		// </test>

		m_InOutMap.SetPosition(sizeof(int) + sizeof(float)*4*(order*stratums_number + stratum));
		pObject->ExportDynamicsData();


		// check
		//m_InOutMap.SetPosition(sizeof(int) + sizeof(float) * 4 * (order*stratums_number + stratum));
		//double f = 0;
		//DMapFile &MapFile = *pObject->m_pMap;
		//MapFile >> f;
		//MapFile >> f;
		//MapFile >> f;
		//MapFile >> f; // TODO check the necessity of multiplication 1.20445
		/////////////////

		++order;
	}
	
	
	return true;
}

void CObjectsModel::DefineControlParams()
{
	for (auto pObject : m_GPAs)
	{
		assert(!pObject->m_SID.empty());
		for (auto param : pObject->m_pParams)
		{
			m_ControlParams[param.second->GetUId()] = param.second;
		}
	}
		
}

int CObjectsModel::CountGroupLosts()
{
	int Losts = 0;
	for_each(m_ParallelShops.begin(), m_ParallelShops.end(), bind(&BObject::I_Count, _1, &Losts, LostGroupsCounter));
	return Losts;
}

void CObjectsModel::ExportData(const string& DataDir)
{
	CFileSystem fs;
	fs.CleanFile(DataDir+"LimitationsGTS.dat");
	fs.CleanFile(DataDir+"MatrixConnections.dat");
	fs.CleanFile(DataDir+"InOutGRS.dat");
	fs.CleanFile(DataDir+"PipeLine.dat");
	fs.CleanFile(DataDir+"Lost.dat");
	fs.CleanFile(DataDir+"Crane.dat");
	fs.CleanFile(DataDir+"CompressorShop.dat");
	fs.CleanFile(DataDir+"GpaNsi.dat");
	fs.CleanFile(DataDir+"AirNsi.dat");
	fs.CleanFile(DataDir+"Lost_ad.dat");
	fs.CleanFile(DataDir+"Aggregate.dat");
	fs.CleanFile(DataDir+"Air.dat");

	ofstream GTSOut,MatrixOut,GRSOut,PipeOut,LostOut,RDOut,ShopOut,GPANSIOut,AVONSIOut,LostShopOut,AirOut,AggregateOut;
	GTSOut.open(DataDir+"LimitationsGTS.dat");
	MatrixOut.open(DataDir+"MatrixConnections.dat");
	GRSOut.open(DataDir+"InOutGRS.dat");
	PipeOut.open(DataDir+"PipeLine.dat");
	LostOut.open(DataDir+"Lost.dat");
	RDOut.open(DataDir+"Crane.dat");
	ShopOut.open(DataDir+"CompressorShop.dat");
	GPANSIOut.open(DataDir+"GpaNsi.dat");
	AVONSIOut.open(DataDir+"AirNsi.dat");
	LostShopOut.open(DataDir+"Lost_ad.dat");
	AirOut.open(DataDir+"Air.dat");
	AggregateOut.open(DataDir+"Aggregate.dat");

	ofstream* ObjectsOut[] = {&PipeOut, &ShopOut, &RDOut, &LostOut};
	
	for_each(m_ObjectsList.begin(), m_ObjectsList.end(), bind(&BObject::InitForExport, _1));

	int PipeCount = 0;
	int ShopCount = 0;
	int LostCount = 0;
	int RDCount = 0;
	int AirCount = 0;
	int AggregateCount = 0;
	int GRSCount = 0;

	for (list <BObject*>::iterator i = m_ObjectsList.begin(); i != m_ObjectsList.end(); i++)
	{
		BObject* pObject = *i;
		if(pObject->CanExport())
		{
			switch(pObject->GetMatrixID())
			{
				case 1:
					PipeCount++;
					break;
				//case 2:
				//	ShopCount++;
				//	break;
				case 3:
					RDCount++;
					break;
				case 4:
					LostCount++;
					break;
				case 5:
					AirCount++;
					break;
				case 6:
					AggregateCount++;
					break;
			}
		}
		else if (pObject->IsIn() || pObject->IsOut())
		{
			GRSCount++;
		}

			//BShop *pShop = dynamic_cast<BShop*>(pObject);
			//if (pShop && pShop->IsFlowMode())
			//{
			//	ShopCount++;
			//}
	}

	ShopCount = m_Shops.size(); // Скидываются все КЦ

	// Информация по ограничениям ГТС
	{
		if (m_pGTS)
			m_pGTS->PrintExportData(GTSOut);
	}

	// Информация о расчетной схеме ГТС
	{
		m_Connections.PrintExportData(MatrixOut);
	}

	GRSOut << GRSCount << endl;
	PipeOut << PipeCount << endl;
	LostOut << LostCount << endl;
	RDOut << RDCount << endl;
	ShopOut << ShopCount << endl;
	LostShopOut << CountGroupLosts() << endl;
	AirOut << AirCount << endl;
	AggregateOut << AggregateCount << endl;


	// Информация по объектам ГТС
	{
		for (list <BObject*>::iterator i = m_ObjectsList.begin(); i != m_ObjectsList.end(); i++)
		{
			BObject* pObject = *i;			

			if (pObject->IsShop())
			{
				pObject->PrintExportData(ShopOut);
			}
			else if (pObject->CanExport())
			{
				int MatrixID = pObject->GetMatrixID();
				if (pObject->IsShopGroup())
				{
					RShopsGroup *pGroup = dynamic_cast<RShopsGroup*>(pObject);
					assert(pGroup);
					pGroup->PrintExportLosts(LostShopOut, *(ObjectsOut[MatrixID-1]));
				}
				else
				{
					pObject->PrintExportData(*(ObjectsOut[MatrixID-1]));
				}
			}
		}
	}

	// Информация по входам/выходам ГТС и отборам
	{
		for (vector <BObject*>::iterator i = m_Ins.begin(); i != m_Ins.end(); i++)
		{
			BObject *pObject = *i;
			pObject->PrintExportData(GRSOut);
		}
		
		for (vector <BObject*>::iterator i = m_Outs.begin(); i != m_Outs.end(); i++)
		{
			BObject *pObject = *i;
			pObject->PrintExportData(GRSOut);
		}
	}

	// НСИ по ГПА
	{
		int nCount = m_NSIGPA.size();
		GPANSIOut << nCount << endl;
		for (unordered_map <int, BNSIGPA*>::iterator i = m_NSIGPA.begin(); i != m_NSIGPA.end(); i++)
		{
			BNSI *pNSI = i->second;
			pNSI->PrintExportData(GPANSIOut);
		}
	}

	// НСИ по АВО
	{
		int nCount = m_NSIAVO.size();
		AVONSIOut << nCount << endl;
		for (unordered_map <int, BNSIAVO*>::iterator i = m_NSIAVO.begin(); i != m_NSIAVO.end(); i++)
		{
			BNSI *pNSI = i->second;
			pNSI->PrintExportData(AVONSIOut);
		}
	}

	GTSOut.flush();
	MatrixOut.flush();
	GRSOut.flush();
	PipeOut.flush();
	LostOut.flush();
	RDOut.flush();
	LostShopOut.flush();
	ShopOut.flush();
	GPANSIOut.flush();
	AVONSIOut.flush();
	AirOut.flush();
	AggregateOut.flush();

	GTSOut.close();
	MatrixOut.close();
	GRSOut.close();
	PipeOut.close();
	LostOut.close();
	RDOut.close();
	LostShopOut.close();
	ShopOut.close();
	GPANSIOut.close();
	AVONSIOut.close();
	AirOut.close();
	AggregateOut.close();
}

void CObjectsModel::InputShopResults(const string &FilePath, bool bResultsToObject /*= false*/)
{
	m_rQtg = 0;
	m_rW = 0;
	m_rN = 0;
	m_rsL = 0;
	m_rsWAVO = 0;
	m_rsQtgCost = 0;
	m_rsWCost = 0;
	m_rsWAVOCost = 0;

	CFileSystem fs;
	if (fs.FileExists(FilePath))
	{
		ifstream in(FilePath);
		string s;
		while(!in.eof())
		{
			int ID = -1;
			in >> ID;								
			getline(in, s);
			BShop *pShop = dynamic_cast<BShop*>(GetObject(ID));
			if(!pShop)
				continue;
			pShop->InputShopResults(in);
			if (bResultsToObject)
			{
				pShop->ResultsToObject();
			}
			pShop->SetCalculated();
			m_rQtg += pShop->m_rsQtg;
			m_rW += pShop->m_rsW;
			m_rN += pShop->m_rsN;
			m_rsL += pShop->m_rsL;
			m_rsWAVO += pShop->m_rsWAVO;

			m_rsQtgCost += pShop->m_rsQtgCost;
			m_rsWCost += pShop->m_rsWCost;
			m_rsWAVOCost += pShop->m_rsWAVOCost;
		}
		in.close();
	}
}

void CObjectsModel::InputEfficiencyResults(const string &ResultShopEf)
{
	for (vector <RShopsGroup*>::iterator i = m_ParallelShops.begin(); i != m_ParallelShops.end(); i++)
	{
		RShopsGroup *pGroup = *i;
		double gA = 0;
		double gB = 0;
		for (vector <BShop*>::iterator j = pGroup->m_pShops.begin(); j != pGroup->m_pShops.end(); j++)
		{
			BShop *pShop = *j;
			if (pShop->m_rsE<1.05)
				continue;
			pShop->m_A = 0;
			pShop->SummA(&pShop->m_A, (gData.m_nKSEfficiencyFormulas == 1)?OptEnums::TypeA::A_ottr:OptEnums::TypeA::A_ettr);
			pShop->m_B = pShop->m_rsQtg*pShop->m_rHin*0.238846/*ккал/м3*//7000.;
			pShop->m_rsEff = pShop->m_B/pShop->m_A*1e6;
			gA += pShop->m_A;
			gB += pShop->m_B;
		}
		pGroup->m_rsEff = (gA>0)?1e3*gB/gA:0;
//		if (gData.m_nKSEfficiencyFormulas == 0)
		{
			pGroup->m_rsEff *= 1e3;
		}
	}

	//CFileSystem fs;
	//if (fs.FileExists(ResultShopEf))
	//{
	//	ifstream in(ResultShopEf);
	//	int n;
	//	string sDumb;
	//	in >> n; // Общее количество КС
	//	getline(in, sDumb);
	//	for(int i = 0; i<n; i++) // Далее в цикле по КС
	//	{
	//		string KSName;
	//		double KSEff;
	//		in >> KSName; // Название КС  (символьная  строка)
	//		in >> KSEff; // Коэф. удельной эффективности КС

	//		getline(in, sDumb);
	//		int n1 = 0;
	//		in >> n1; // количество подстанций
	//		getline(in, sDumb);
	//		for(int i = 0; i<n1; i++) // Далее в цикле по подстанциям
	//		{
	//			int SubKS;
	//			double SubKSEff;
	//			in >> SubKS; // Номер подстанции 
	//			in >> SubKSEff; // Коэф. удельной эффективности подстанции
	//			getline(in, sDumb);
	//			int n2 = 0; // количество КЦ в подстанции
	//			in >> n2;
	//			getline(in, sDumb);
	//			for(int i = 0; i<n2; i++) // Далее в цикле по КЦ
	//			{
	//				int ShopID;
	//				double ShopEff;
	//				in >> ShopID;
	//				in >> ShopEff;
	//				BShop *pShop = dynamic_cast<BShop*>(GetObject(ShopID));
	//				if(!pShop)
	//					continue;
	//				pShop->m_rsEff = ShopEff;
	//				if (pShop->m_pGroup)
	//				{
	//					pShop->m_pGroup->m_rsEff = SubKSEff;
	//				}
	//			}
	//			getline(in, sDumb);
	//		}
	//	}
	//	in.close();
	//}
}

bool CObjectsModel::ImportResults(const string& ResultsDir)
{
	CFileSystem fs;
	m_rEdgesCount = 0;
	ResetAlerts();

	string CurrentDir = fs.GetCurrentDirectory()+"\\";
	if (ResultsDir.find(":\\") != string::npos)
		CurrentDir = "";

	for_each(m_ObjectsList.begin(), m_ObjectsList.end(), bind(&BObject::ClearResults, _1));

	bool bError = fs.FileExists(ResultsDir + "Error.dat");
	m_rDisbalances.clear();
	m_rSummDisbalance = 0;
	if (bError)
	{
		string s;
		string dbPath = ResultsDir + "Balance.dat";
		if (fs.FileExists(dbPath))
		{
			int n = 0;
			ifstream in(dbPath);
			in >> n;
			getline(in, s);
			// Цикл по ребрам расчетной схемы ГТС (объектам)
			for(int i = 0; i<n; i++)
			{
				Disbalance db;
				in >> db.m_Node;
				in >> db.m_Q;
				in >> db.m_P;
				m_rSummDisbalance += fabs(db.m_Q);
				m_rDisbalances.push_back(db);
				getline(in, s);
			}
		}
	}

	if (!bError)
	{
		string s;
		string Results = ResultsDir + "Result.dat";

		int nEdgesCount = 0;
		int nGRSCount = 0;
		if (fs.FileExists(Results))
		{
			m_RestrictionsP = 0;

			ifstream in(Results);
			getline(in, s);
			in >> nEdgesCount;
			getline(in, s);
			// Цикл по ребрам расчетной схемы ГТС (объектам)
			for(int i = 0; i<nEdgesCount; i++)
			{
				int ID = -1;
				in >> ID;

				BObject *pObject = GetObject(ID);
				if(pObject)
				{
					pObject->ImportResults(in);
					pObject->SetCalculated();
					m_rEdgesCount += pObject->m_CalculatedEdgesCount;
				}
				getline(in, s);
			}
			// Цикл по поставщикам и потребителям (ГРС) расчетной схемы ГТС
			in >> nGRSCount;
			getline(in, s);
			for(int i = 0; i<nGRSCount; i++)
			{
				int ID = -1;
				in >> ID;
				BObject *pObject = GetObject(ID);
				if(pObject)
				{				
					pObject->ImportResults(in);
					pObject->SetCalculated();
				}
				getline(in, s);
			}
			in.close();
		}

		string ResultCompressorShop = ResultsDir + "ResultCompressorShop.dat";
		if (fs.FileExists(ResultCompressorShop))
		{
			InputShopResults(ResultCompressorShop);
		}

		string ResultShopEf = ResultsDir + "ResultShopEf.dat";
		InputEfficiencyResults(ResultShopEf);

		string ResultCraneIdent = ResultsDir + "ResultCraneIdent.dat";
		if (fs.FileExists(ResultCraneIdent))
		{
			ifstream in(ResultCraneIdent);
			int ValvesCount = 0;
			in >> ValvesCount;
			getline(in, s);
			for (int i = 0; i<ValvesCount; i++)
			{
				int ID = -1;
				in >> ID;
				if(in.eof())
					break;
				BObject *pObject = GetObject(ID);
				if(pObject)
				{				
					pObject->ImportAdaptation(in);
					pObject->SetCalculated();
				}
				getline(in, s);
			}
			in.close();
		}
	}

	for_each(m_ObjectsList.begin(), m_ObjectsList.end(), bind(&BObject::PostCalculate, _1, false)); // +alerts
	
	// сохранение удачного расчета
	if (!bError)
	{
		string PrevResults = CurrentDir+ResultsDir+"prev";
		if (!fs.DirectoryExists(PrevResults))
			fs.MakeDirectory(PrevResults);

//		fs.DeleteDirectory(PrevResults, true);
		
		PrevResults += "\\";

		list <CAlert*> *pFlowbacks = GetAlerts(OptEnums::AlertType::A_Shop_Flowback);
		list <CAlert*> *pPmaxExcess = GetAlerts(OptEnums::AlertType::A_Excess_Shop_Pmax);
		list <CAlert*> *pNmaxExcess = GetAlerts(OptEnums::AlertType::A_Excess_ShopGPA_Kz);
		bool bCriticalAlerts = pFlowbacks || pPmaxExcess || pNmaxExcess;
		if (!bCriticalAlerts)
		{
			fs.CopyFile(CurrentDir+ResultsDir+"Result.dat", PrevResults+"Result.dat");
			fs.CopyFile(CurrentDir+ResultsDir+"ResultCompressorShop.dat", PrevResults+"ResultCompressorShop.dat");
			fs.CopyFile(CurrentDir+ResultsDir+"ResultShopEf.dat", PrevResults+"ResultShopEf.dat");
			fs.CopyFile(CurrentDir+ResultsDir+"ResultCraneIdent.dat", PrevResults+"ResultCraneIdent.dat");
		}
	}

	// Расчет показателей энергоэффективности ГТС
	// СТО 2-1.20-114-2007, ф-ла 9.4
	m_A_ttr = 0;
	m_A_ettr = 0;
	m_A_ottr = 0;

	if (!IsFlowMode())
		int aa=0;
	// ТТР
	{
		for_each(m_Pipes.begin(), m_Pipes.end(), bind(&BObject::SummA, _1, &m_A_ttr, OptEnums::TypeA::A_ttr)); // ЛЧ
	}

	// ЭТТР
	{
		double c = 3.912*1e-2;
		double A1 = 0; // входы
		double A2 = 0; // выходы
		double A3 = 0; // КС

		for_each(m_Ins.begin(), m_Ins.end(), bind(&BObject::SummA, _1, &A1, OptEnums::TypeA::A_ettr)); // входы
		for_each(m_Outs.begin(), m_Outs.end(), bind(&BObject::SummA, _1, &A2, OptEnums::TypeA::A_ettr)); // выходы
		for_each(m_Shops.begin(), m_Shops.end(), bind(&BObject::SummA, _1, &A3, OptEnums::TypeA::A_ettr)); // КС

		m_A_ettr = (A1-A2+A3);
	}

	// ОТТР
	{
		double A1 = 0; // входы
		double A2 = 0; // выходы
		double A3 = 0; // КС

		for_each(m_Pipes.begin(), m_Pipes.end(), bind(&BObject::SummA, _1, &A1, OptEnums::TypeA::A_ottr)); // входы

		m_A_ottr = (A1-A2+A3);
	}

	// Суммарные затраты топливного газа и электроэнергии
	{
		m_rQtg = 0;
		m_rW = 0;
		m_rN = 0;
		m_rsL = 0;
		m_rsWAVO = 0;

		m_rsQtgCost  = 0;
		m_rsWCost = 0;
		m_rsWAVOCost = 0;

		m_rTinDelta = 0;
		
		double Tga = 0; // средневзвешенное отклонение температур газа на входе КЦ от температур грунта
		double Qgs = 0; // общий объем транспорта газа через все КС

		for (vector <RShopsGroup*>::iterator i = m_ParallelShops.begin(); i != m_ParallelShops.end(); i++)
		{
			RShopsGroup *pGroup = *i;
			if (!IsFlowMode())
			{
				double Ta = 0; // средневзвешенное отклонение температур газа на входе КЦ от температур грунта
				double Qs = 0; // общий объем транспорта газа через КС
				for (vector <BShop*>::iterator j = pGroup->m_pShops.begin(); j != pGroup->m_pShops.end(); j++)
				{
					BShop *pShop = *j;
					m_rQtg += pShop->m_rsQtg;
					m_rW += pShop->m_rsW;
					m_rN += pShop->m_rsN;
					m_rsL += pShop->m_rsL;
					m_rsWAVO += pShop->m_rsWAVO;

					m_rsQtgCost += pShop->m_rsQtgCost;
					m_rsWCost += pShop->m_rsWCost;
					m_rsWAVOCost += pShop->m_rsWAVOCost;
					
					Qs += pShop->m_rQin;
					Ta += pShop->m_rTin*pShop->m_rQin;
				}
				if (Qs)
					Ta /= Qs;

				Tga += fabs(Ta-pGroup->m_Tftg)*Qs;
				Qgs += Qs;

				//m_rTinDelta += fabs(Ta-pGroup->m_Tftg);
			}
			else
			{
				m_rQtg += pGroup->m_dQ;
				Qgs += pGroup->m_rQin;
				Tga += fabs(pGroup->m_rTin-pGroup->m_Tftg)*pGroup->m_rQin;

				//m_rTinDelta += fabs(pGroup->m_Tin-pGroup->m_Tftg);

			}			
		}

		if (Qgs)
			Tga /= Qgs;

		m_rTinDelta = Tga; // средневзвешенное отклонение температур газа на входах КЦ от температур грунта
	}

	return !bError;
}

void CObjectsModel::ExportResults(ostream &ResultsOut, vector <BObject*> &ObjectsList)
{
	for (vector <BObject*>::iterator i = ObjectsList.begin(); i != ObjectsList.end(); i++)
	{
		BObject *pObject = *i;
		if (!pObject->m_bCalculated)
			continue;
		pObject->ExportResults(ResultsOut);
		ResultsOut << endl;
	}
}

void CObjectsModel::ExportResults(const string& Dir)
{
	CFileSystem fs;

	// Файл Result.dat
	{
		string ResultsPath(Dir + "Result.dat");
		fs.CleanFile(ResultsPath);
		ofstream ResultsOut;
		ResultsOut.open(ResultsPath);

		ResultsOut << "0.000000 00:03" << endl;

		ResultsOut << m_rEdgesCount << endl;
		ExportResults(ResultsOut, m_Pipes);
		ExportResults(ResultsOut, m_Losts);
		ExportResults(ResultsOut, m_RDValves);
		ExportResults(ResultsOut, m_Shops);
		ExportResults(ResultsOut, m_Valves);

		int nGRSCount = m_Ins.size() + m_Outs.size();
		ResultsOut << nGRSCount << endl;
		ExportResults(ResultsOut, m_Ins);
		ExportResults(ResultsOut, m_Outs);
		ResultsOut.close();
	}

	// Файл ResultCompressorShop.dat
	{
		string ResultsPath(Dir + "ResultCompressorShop.dat");
		fs.CleanFile(ResultsPath);
		ofstream ResultCS;
		ResultCS.open(ResultsPath);
		for (vector <BObject*>::iterator i = m_Shops.begin(); i != m_Shops.end(); i++)
		{
			BShop *pShop = dynamic_cast<BShop*>(*i);
			assert(pShop);
			pShop->ExportShopResults(ResultCS);
		}
		ResultCS.close();
	}
	
	// Файл ResultCraneIdent.dat
	{
		string ResultsPath(Dir + "ResultCraneIdent.dat");
		fs.CleanFile(ResultsPath);
		ofstream ResultValves;
		ResultValves.open(ResultsPath);
		int nCount = m_RDValves.size();
		ResultValves << nCount << endl;
		for (vector <BObject*>::iterator i = m_RDValves.begin(); i != m_RDValves.end(); i++)
		{
			BObject *pValve = *i;
			pValve->ExportAdaptation(ResultValves);
			ResultValves << endl;
		}
		ResultValves.close();
	}
}

void CObjectsModel::SetFlowMode(bool bFlowModel)
{
	for_each(m_ParallelShops.begin(), m_ParallelShops.end(), bind(&RShopsGroup::SetFlowMode, _1, bFlowModel));
	m_bFlowMode = bFlowModel;
}

}