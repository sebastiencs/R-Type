//
// ISystemFile.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Dec 27 02:06:21 2015 chapui_s
// Last update Sun Dec 27 02:06:21 2015 chapui_s
//

#ifndef ISYSTEMFILE_H_
# define ISYSTEMFILE_H_

# include <list>
# include <string>
# include <memory>

using Files = std::list<std::string>;

class		ISystemFile
{
public:
  ISystemFile();
  virtual ~ISystemFile() {};

  virtual bool	exist(const std::string &name); // is file or directory exist
  virtual bool	isDirectory(const std::string &name); // is a directory ( not a file )
  virtual const Files	&getListFiles(const std::string &dir); // return files list in directory
};

using ISystemFile_UniquePtr = std::unique_ptr<ISystemFile>;

#endif /* !ISYSTEMFILE_H_ */
