//
// SystemFileUnix.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Dec 27 02:13:48 2015 chapui_s
// Last update Sun Dec 27 02:13:48 2015 chapui_s
//

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "Debug.hh"
#include "SystemFileUnix.hh"

SystemFile::SystemFile()
{
}

SystemFile::~SystemFile()
{
}

bool	SystemFile::exist(const std::string &name)
{
  return (access(name.c_str(), F_OK | X_OK) ? (false) : (true));
}

bool	SystemFile::isDirectory(const std::string &name)
{
  struct stat st;

  stat(name.c_str(), &st);
  return ((S_ISDIR(st.st_mode)) ? (true) : (false));
}

const Files	&SystemFile::getListFiles(const std::string &dir)
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
