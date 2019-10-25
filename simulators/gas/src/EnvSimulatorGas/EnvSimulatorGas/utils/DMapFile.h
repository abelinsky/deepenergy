#pragma once

namespace Utils
{
	class DMapFile
	{
	public:
		DMapFile();
		virtual ~DMapFile(void);
	
	public:
		std::string m_Name;

		/// file handle
		HANDLE m_hFile;

		/// Windows handle to memory mapping of _file
		HANDLE m_hMap;

		/// pointer to the file contents mapped into memory
		void* m_pData;

		/// file size
		int m_Size;

		int m_Offset;


		bool Open(std::string filename);
		void Close();

		int Get(void *P, int& nOffset, size_t count);
		int Set(void *P, int& nOffset, size_t count);
		
		void* operator->()
		{
			return m_pData;
		}

		void Reset()
		{
			m_Offset = 0;
		}

		int SetPosition(int nOffset)
		{
			return (m_Offset = nOffset);
		}

		int Get(void *P, size_t count)
		{
			return Get(P, m_Offset, count);
		}

		int Set(void *P, size_t count)
		{
			return Set(P, m_Offset, count);
		}

		inline bool IsOpened() { return m_pData != nullptr; }
	};

	template <class T>	DMapFile& operator << (DMapFile& map, T d)
	{
		map.Set(&d, sizeof(T));
		return map;
	}

	template <class T> DMapFile& operator >> (DMapFile& map, T& d)
	{
		map.Get(&d, sizeof(T));
		return map;
	}
}