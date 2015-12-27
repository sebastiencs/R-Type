//
// DynamicLib.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Dec 27 02:46:12 2015 chapui_s
// Last update Sun Dec 27 02:46:12 2015 chapui_s
//

#ifndef DYNAMICLIB_H_
# define DYNAMICLIB_H_

# ifdef __unix__
#  include "DynamicLibUnix.hh"
using DynamicLib = DynamicLibUnix;
# elif defined (_WIN32)
#  include "DynamicLibWin.hh"
using DynamicLib = DynamicLibWin;
# else
#  error "Unknown platform"
# endif

#endif /* !DYNAMICLIB_H_ */
