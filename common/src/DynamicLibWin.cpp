//
// DynamicLibWin.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 15:40:25 2015 chapui_s
// Last update Wed Nov 11 15:40:25 2015 chapui_s
//

#include <iostream>
#include "DynamicLibWin.hh"
#include "IPlugin.hh"

DynamicLibWin::DynamicLibWin(const std::string &lib)
  : _lib(0)
{
  (void)_lib;
  _unused = []() { std::cerr << "Error: Using a wrong function" << std::endl; };
  DEBUG_MSG("DynamicLibWin created");
}

DynamicLibWin::~DynamicLibWin()
{
  DEBUG_MSG("DynamicLibWin deleted");
}

const Enemy_SharedPtr DynamicLibWin::getEnemy(const std::string &func) const
{
	IPlugin		*(*plugin)();

	if (!(plugin = reinterpret_cast<IPlugin *(*)()>(dlsym(_lib, func.c_str())))) {
		std::cerr << "Can't get symbol " << func << " : " << dlerror() << std::endl;
		return (nullptr);
	}
	else {
		auto e = plugin();
		return ((e) ? (e->getEnemy()) : (nullptr));
	}
}
