//
// DynamicLibUnix.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 11:45:13 2015 chapui_s
// Last update Wed Nov 11 11:45:13 2015 chapui_s
//

#ifndef DYNAMICLIBUNIX_H_
# define DYNAMICLIBUNIX_H_

# include <dlfcn.h>
# include "IDynamicLib.hh"
# include "Debug.hh"

class		DynamicLibUnix : public IDynamicLib
{
private:
  void			*_lib;
  std::function<void()>	_unused;

public:
  DynamicLibUnix(const std::string &);
  virtual ~DynamicLibUnix();

  virtual std::function<void()>	getFunc(const std::string &) const;
};

#endif /* !DYNAMICLIBUNIX_H_ */
