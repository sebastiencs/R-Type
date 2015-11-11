//
// DynamicLib.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 13:34:31 2015 chapui_s
// Last update Wed Nov 11 13:34:31 2015 chapui_s
//

#include <iostream>
#include "DynamicLibUnix.hh"

DynamicLibUnix::DynamicLibUnix(const std::string &lib)
  : _lib(0)
{
  _unused = []() { std::cerr << "Error: Using a wrong function" << std::endl; };

  if (!(_lib = dlopen(lib.c_str(), RTLD_LAZY | RTLD_GLOBAL | RTLD_NOW))) {
    std::cerr << "Can't load library " << lib << " : " << dlerror() << std::endl;
    return ;
  }
  DEBUG_MSG("DynamicLibUnix created");
}

DynamicLibUnix::~DynamicLibUnix()
{
  DEBUG_MSG("DynamicLibUnix deleted");
  if (_lib) {
    dlclose(_lib);
  }
}

std::function<void()>	DynamicLibUnix::getFunc(const std::string &func) const
{
  void			*symbole = 0;

  if (!(symbole = dlsym(_lib, func.c_str()))) {
    std::cerr << "Can't get symbol " << func << " : " << dlerror() << std::endl;
    return (_unused);
  }
  else {
    return (*reinterpret_cast<std::function<void()>*>(symbole));
  }
}
