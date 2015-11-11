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

std::function<void()>	DynamicLibWin::getFunc(const std::string &func) const
{
  static std::function<void()> f = []() {};
  (void)func;
  return (f);
}
