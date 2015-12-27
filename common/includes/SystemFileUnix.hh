//
// SystemFileUnix.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Dec 27 02:12:10 2015 chapui_s
// Last update Sun Dec 27 02:12:10 2015 chapui_s
//

#ifndef SYSTEMFILEUNIX_H_
# define SYSTEMFILEUNIX_H_

# include "ISystemFile.hh"

class		SystemFile : public ISystemFile
{
private:
  Files		_files;

public:
  SystemFile();
  virtual ~SystemFile();

  virtual bool	exist(const std::string &name);
  virtual bool	isDirectory(const std::string &name);
  virtual const Files	&getListFiles(const std::string &dir);
};

#endif /* !SYSTEMFILEUNIX_H_ */
