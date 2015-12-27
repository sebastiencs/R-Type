//
// SystemFileUnix.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Dec 27 02:13:48 2015 chapui_s
// Last update Sun Dec 27 02:13:48 2015 chapui_s
//

#include "SystemFileWin.hh"
#include "Debug.hh"

SystemFileWin::SystemFileWin()
{
}

SystemFileWin::~SystemFileWin()
{
}

bool	SystemFileWin::exist(const std::string &name)
{
  DWORD type = GetFileAttributesA(name.c_str());
  if (type == INVALID_FILE_ATTRIBUTES)
    return false;

  if (type & FILE_ATTRIBUTE_DIRECTORY)
    return true;

  return false; 
}

bool	SystemFileWin::isDirectory(const std::string &name)
{
  DWORD type = GetFileAttributesA(name.c_str());

  return ((type & FILE_ATTRIBUTE_DIRECTORY) ? true : false);
}

const Files	&SystemFileWin::getListFiles(const std::string &dir)
{
  _files.clear();

  TCHAR szDir[MAX_PATH];
  WIN32_FIND_DATA ffd;

  sprintf_s(szDir, "%s/*.*", dir.c_str());
  HANDLE hFind = FindFirstFile(szDir, &ffd);
  if (hFind != INVALID_HANDLE_VALUE) {
	do {
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			_files.push_back(ffd.cFileName);
		}
	}
	while (FindNextFile(hFind, &ffd) != 0);
	FindClose(hFind);
  }
  else {
	  DEBUG_MSG("FindFirstFile failed");
  }
  return (_files);
}