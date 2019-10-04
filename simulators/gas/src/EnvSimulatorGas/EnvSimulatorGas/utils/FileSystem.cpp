#include "pch.h"
#include "FileSystem.h"

namespace Utils {

	CFileSystem::CFileSystem()
	{
	}

	CFileSystem::~CFileSystem()
	{
	}

	bool CFileSystem::CleanFile(const string& Path)
	{
		return fs::remove(Path);
	}

	bool CFileSystem::CopyFile(const string& SourceFileName, const string& DestFileName, BOOL bCleanIfExists)
	{
		if (!fs::exists(SourceFileName))
			return false;
		bool bResult = fs::copy_file(SourceFileName, DestFileName, fs::copy_options::overwrite_existing);
		if (bCleanIfExists)
			CleanFile(SourceFileName);
		return bResult;
	}

	bool CFileSystem::Remove(const string& path)
	{
		return fs::remove(path);
	}

	bool CFileSystem::RemoveAll(const string& DirPath)
	{
		try
		{
			return fs::remove_all(DirPath);
		}
		catch (...)
		{
			DoLogForced("Cannot remove path: " + DirPath);
			return false;
		}
		return true;
		
	}

	bool CFileSystem::DirectoryExists(const string& Path)
	{
		return fs::exists(Path);
	}

	bool CFileSystem::FileExists(const string& PathAndFileName)
	{
		return fs::exists(PathAndFileName);
	}

	string CFileSystem::GetCurrentDirectory()
	{
		return fs::current_path().string();
	}

	bool CFileSystem::MakeDirectory(const string& NewDirectory)
	{
		return fs::create_directories(NewDirectory);
	}

}