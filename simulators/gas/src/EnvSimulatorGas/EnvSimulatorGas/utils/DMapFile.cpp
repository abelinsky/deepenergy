#include "pch.h"
#include "DMapFile.h"

namespace Utils {

	DMapFile::DMapFile()
	{
		m_hFile = nullptr;
		m_hMap = nullptr;
		m_pData = nullptr;
		m_Size = 0;
	}

	DMapFile::~DMapFile()
	{
		Close();
	}

	bool DMapFile::Open(std::string filename)
	{
		DoLogForced("Trying to open shared memory file: " + filename);

		m_Name = filename;
		// open file
		m_hFile = ::CreateFileA(m_Name.c_str(), GENERIC_WRITE | GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		if (m_hFile == INVALID_HANDLE_VALUE)
		{
			DoLogForced("Error opening shared memory file:" + filename);
			m_hFile = nullptr;
			return false;
		}

		// file size
		LARGE_INTEGER result;
		if (!GetFileSizeEx(m_hFile, &result))
			return false;
		m_Size = static_cast<uint64_t>(result.QuadPart);

		// convert to mapped mode
		m_hMap = ::CreateFileMapping(m_hFile, NULL, PAGE_READWRITE, 0, 0, NULL);
		if (!m_hMap)
		{
			DoLogForced("Error CreateFileMapping:" + filename);
			return false;
		}
		// get memory address
		m_pData = MapViewOfFile(m_hMap, FILE_MAP_WRITE, 0, 0, m_Size);

		// initial mapping
		//remap(0, mappedBytes);

		if (!m_pData)
		{
			DoLogForced("Error MapViewOfFile:" + filename);
			return false;
		}

		m_Offset = 0;
		DoLogForced("Shared memory file has been opened successfully: " + m_Name);

		return true;
	}

	void DMapFile::Close()
	{
		if (m_pData)
		{
			::UnmapViewOfFile(m_pData);
			m_pData = nullptr;
		}

		if (m_hMap)
		{
			::CloseHandle(m_hMap);
			m_hMap = nullptr;
		}

		// close underlying file
		if (m_hFile)
		{
			::CloseHandle(m_hFile);
			m_hFile = 0;
		}

		m_Size = 0;
	}

	int DMapFile::Get(void *P, int& nOffset, size_t count)
	{
		if (m_pData)
		{
			if (((nOffset + count) <= m_Size) && (nOffset >= 0))
			{
				memcpy(P, ((BYTE *)m_pData + nOffset), count);
				nOffset += count;
			}
			else
			{
				DoLog("Map reading error to " + m_Name + " " + itos(m_Size) + " " + itos(nOffset) + " " + itos(count));
			}
		}
		else
		{
			DoLog("NULL data reading " + m_Name + " " + itos(m_Size) + " " + itos(nOffset) + " " + itos(count));
		}
		return nOffset;
	}

	int DMapFile::Set(void *P, int& nOffset, size_t count)
	{
		if (m_pData)
		{
			if (((nOffset + count) <= m_Size) && (nOffset >= 0))
			{
				memcpy(((BYTE *)m_pData + nOffset), P, count);
				nOffset += count;
			}
			else
			{
				DoLog("Map writing error to " + m_Name + " " + itos(m_Size) + " " + itos(nOffset) + " " + itos(count));
			}
		}
		else
		{
			DoLog("NULL data writing " + m_Name + " " + itos(m_Size) + " " + itos(nOffset) + " " + itos(count));
		}
		return nOffset;
	}

}