#include "pch.h"
#include "BNSIGPA.h"

namespace NSI {

BNSIGPA::BNSIGPA(void)
{
	m_nCharacteristic = 0;
	m_DriveType = 0;
	m_bWholeHead = 0;
	m_kNmax = -1;
	m_N = 0;
	m_Qtg = 0;
	m_H = 34541;
	m_Tair = 15;
	m_Pair = 1;
	m_Qmin = 0;
	m_Qmax = 0;
	m_nmin = 0;
	m_nmax = 0;
	m_dP = 0;
	m_Z = 0;
	m_T = 0;
	m_R = 0;
	m_wKPD = 1;
	m_mKPD = 1;
	m_kUtil = 1;
	m_mechKPD = 1;
}

BNSIGPA::~BNSIGPA(void)
{
}

bool BNSIGPA::CheckLoadedData(string& Error)
{
	return true;
}

void BNSIGPA::LoadData(istream &in)
{
	string s;

	m_kN.clear();
	m_kK.clear();
	m_kE.clear();
	m_ktIntervals.clear();

	//	2 строка
	in >> m_ID;
	in >> m_nCharacteristic;
	in >> m_DriveType;
	in >> m_bWholeHead;
	if (!eol(in))
		in >> m_kNmax;
	getline(in, s);
	//	3,4 строки
	if (m_nCharacteristic>0)
	{
		vector <double> *pCoeffs = NULL;
		switch (m_nCharacteristic)
		{
		case 1:
		case 3:
			{
				pCoeffs = &m_kN;
				break;
			}
		case 2:
			{
				pCoeffs = &m_kE;
				break;
			}
		}

		int Degree; // степень полинома
		in >> Degree;
		for (int i = 0; i<=Degree; i++)
		{
			double k;
			in >> k;		
			if (pCoeffs)
				pCoeffs->push_back(k);
		}
		getline(in, s);
		in >> Degree;
		for (int i = 0; i<=Degree; i++)
		{
			double k;
			in >> k;
			m_kK.push_back(k);
		}
		getline(in, s);
	}

	//	5 строка
	in >> m_N;
	in >> m_Qtg;
	in >> m_H;
	in >> m_Tair;
	in >> m_Pair;
	getline(in, s);

	//	6 строка
	in >> m_Qmin;
	in >> m_Qmax;
	in >> m_nmin;
	in >> m_nmax;
	in >> m_dP;
	getline(in, s);

	//	7 строка
	in >> m_Z;
	in >> m_T;
	in >> m_R;
	getline(in, s);

	//	8 строка
	in >> m_wKPD;
	in >> m_mKPD;
	in >> m_kUtil;
	in >> m_mechKPD;
	getline(in, s);
	
	//	9 строка
	int iCount;
	in >> iCount;
	for (int i = 0; i<iCount; i++)
	{
		getline(in, s);
		KTInterval ktInt;
		in >> ktInt.m_Tmin;
		in >> ktInt.m_Tmax;
		in >> ktInt.m_kt;
		in >> ktInt.m_T;
		m_ktIntervals.push_back(ktInt);
	}
}

void BNSIGPA::PrintExportData(ostream &out)
{
	//	2 строка
	out <<
		m_ID << " " << 
		m_nCharacteristic << " " << 
		m_DriveType << " " << 
		m_bWholeHead;
	
	if (m_kNmax>0)
	{
		out << " " << m_kNmax << endl;
	}
	else
	{
		out << endl;
	}


	//	3,4 строки
	if (m_nCharacteristic>0)
	{
		vector <double> *pCoeffs = NULL;
		switch (m_nCharacteristic)
		{
		case 1:
		case 3:
			{
				pCoeffs = &m_kN;
				break;
			}
		case 2:
			{
				pCoeffs = &m_kE;
				break;
			}
		}

		int Degree = 0;
		if (pCoeffs)
		{
			Degree = pCoeffs->size()-1; // степень полинома
			out << Degree;
			for (vector <double>::iterator i = pCoeffs->begin(); i != pCoeffs->end(); i++)
			{
				double k = *i;
				out << " " << k;
			}
			out << endl;
		}

		Degree = m_kK.size()-1;
		out << Degree;
		for (vector <double>::iterator i = m_kK.begin(); i != m_kK.end(); i++)
		{
			double k = *i;
			out << " " << k;
		}
		out << endl;
	}
	
	//	5 строка		
	out <<
		m_N << " " << 
		m_Qtg << " " << 
		m_H << " " << 
		m_Tair << " " << 
		m_Pair << 
	endl;

	//	6 строка
	double QMin = m_Qmin;
	double QMax = m_Qmax;
	double nmin = m_nmin;
	double nmax = m_nmax;
	//nmin = 0.3;  // временно
	//nmax = 1.2; // временно
	//QMin = 10; // временно
	//QMax = 2000;
	if (!gData.m_bControlRestrictions)
	{
		nmin = 0.3;
		nmax = 1.2;
	}

	out <<
		QMin << " " << 
		QMax << " " << 
		nmin << " " << 
		nmax << " " << 
		m_dP << 
	endl;

	//	7 строка
	out <<
		m_Z << " " << 
		m_T << " " << 
		m_R << 
	endl;

	//	8 строка
	out <<
		m_wKPD << " " << 
		m_mKPD << " " << 
		m_kUtil << " " << 
		m_mechKPD <<
	endl;
		
	//	9 строка
	int iCount = m_ktIntervals.size();
	out << iCount;
	for (vector <KTInterval>::iterator i = m_ktIntervals.begin(); i != m_ktIntervals.end(); i++)
	{
		KTInterval &ktInt = *i;
		out <<
			endl <<
			ktInt.m_Tmin << " " << 
			ktInt.m_Tmax << " " << 
			ktInt.m_kt << " " << 
			ktInt.m_T;
	}
	out << endl;
}

void BNSIGPA::CopyForceParams(BNSIGPA *pSource)
{
	m_nCharacteristic = pSource->m_nCharacteristic;		// 1 – есть (мощность и кпд), 2 – есть (ст. сжатия и кпд)
	m_bWholeHead = pSource->m_bWholeHead;				// признак (1-полнонапорный/ 0-нет)
	m_kN = pSource->m_kN;								// коэффициенты аппроксимации мощностной характеристики	
	m_kK = pSource->m_kK;								// коэффициенты аппроксимации характеристики политропического КПД
	m_kE = pSource->m_kE;								// коэффициенты аппроксимации напорной характеристики
	m_Qmin = pSource->m_Qmin;							// минимально-допустимый приведенный расход [м3/мин]	
	m_Qmax = pSource->m_Qmax;							// максимально-допустимый приведенный расход [м3/мин]	
	m_dP = pSource->m_dP;								// потери давления между ступенями сжатия  [ата]
	m_Z = pSource->m_Z;									// коэффициент  сжимаемости приведения
	m_T = pSource->m_T;									// температура приведения [0С]
	m_R = pSource->m_R;									// газовая постоянная приведения [Дж/кг град]
	m_mechKPD = pSource->m_mechKPD;						// механический КПД
}

void BNSIGPA::CopyDriveParams(BNSIGPA *pSource)
{
	m_DriveType = pSource->m_DriveType;				   // признак привода (0-эл.привод/ 1-ГТУ/ 2-ГМК)
	m_kNmax = pSource->m_kNmax;						   // Максимально-допустимое отношение расп. мощности к номинальной
	m_N = pSource->m_N;								   // номинальная мощность [кВт]	
	m_Qtg = pSource->m_Qtg;							   // номинальный расход топливного газа с учетом тех. сос. [млн.м3/сут]		
	m_H = pSource->m_H;								   // номинальная низшая теплота сгорания [кДж/м3]					
	m_Tair = pSource->m_Tair;						   // номинальная температура воздуха на входе ГТУ [0С]			
	m_Pair = pSource->m_Pair;						   // номинальное значение давления воздуха [ата]			
	m_nmin = pSource->m_nmin;						   // минимально-допустимые относительные обороты			
	m_nmax = pSource->m_nmax;						   // минимально-допустимые относительные обороты			
	m_wKPD = pSource->m_wKPD;						   // КПД электродвигателя
	m_mKPD = pSource->m_mKPD;						   // КПД мультипликатора			
	m_kUtil = pSource->m_kUtil;						   // коэффициент  влияния системы утилизации	
	m_ktIntervals = pSource->m_ktIntervals;			   // Интервалы коэффициента kt						
}

}