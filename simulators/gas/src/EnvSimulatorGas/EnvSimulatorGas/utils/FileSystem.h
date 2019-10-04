#pragma once

// See https://medium.com/@sshambir/%D0%BF%D1%80%D0%B8%D0%B2%D0%B5%D1%82-std-filesystem-4c7ed50d5634

namespace Utils
{
	class CFileSystem
	{
	public:
		CFileSystem(void);
		virtual ~CFileSystem(void);
			
		bool CleanFile(const string& Path);

		bool CopyFile(const string& SourceFileName, const string& DestFileName, BOOL bCleanIfExists = FALSE);

		bool Remove(const string& path);

		bool RemoveAll(const string& DirPath);

		bool DirectoryExists(const string& Path);

		bool FileExists(const string& PathAndFileName);

		string GetCurrentDirectory();

		bool MakeDirectory(const string& NewDirectory);

	};
}