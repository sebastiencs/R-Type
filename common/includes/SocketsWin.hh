//
// SocketsWin.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 24 14:20:43 2015 chapui_s
// Last update Tue Nov 24 14:20:43 2015 chapui_s
//

#ifndef SOCKETSWIN_H_
# define SOCKETSWIN_H_

# if _MSC_VER > 1000
#  pragma once
# endif

# ifndef _WINDOWS_
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#  undef WIN32_LEAN_AND_MEAN
# endif

# include <winsock2.h>

# pragma comment(lib, "ws2_32.lib")

#endif /* !SOCKETSWIN_H_ */
