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

  DIR *dp;
  struct dirent *ep;

  dp = opendir (dir.c_str());
  if (dp) {

    while ((ep = readdir(dp))) {
      DEBUG_MSG(std::string("Files: ") + ep->d_name);
      _files.push_back(ep->d_name);
    }

    closedir(dp);
  }
  else {
    DEBUG_MSG("Can't open directory");
  }

  return (_files);
}
