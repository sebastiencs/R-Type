//
// SystemFileUnix.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Dec 27 02:12:10 2015 chapui_s
// Last update Sun Dec 27 02:12:10 2015 chapui_s
//

#ifndef SYSTEMFILEWIN_H_
# define SYSTEMFILEWIN_H_

# include <string>
# include "SocketsWin.hh"
# include "ISystemFile.hh"

class		SystemFileWin : public ISystemFile
{
private:
  Files		_files;

public:
  SystemFileWin();
  virtual ~SystemFileWin();

  virtual bool	exist(const std::string &name);
  virtual bool	isDirectory(const std::string &name);
  virtual const Files	&getListFiles(const std::string &dir);
};

#endif /* !SYSTEMFILEWIN_H_ */
