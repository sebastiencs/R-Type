//
// Socket.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 03:50:52 2015 chapui_s
// Last update Wed Nov 11 03:50:52 2015 chapui_s
//

#ifndef SOCKET_H_
# define SOCKET_H_

# ifdef __unix__

#   include "SocketTCPUnix.hh"
#   include "SocketUDPUnix.hh"
typedef SocketTCPUnix SocketTCP;
typedef SocketUDPUnix SocketUDP;

# elif defined(_WIN32)

#   include "SocketTCPWin.hh"
#   include "SocketUDPWin.hh"
typedef SocketTCPWin SocketTCP;
typedef SocketUDPWin SocketUDP;

# else

#   error "Platform Unknown"

# endif

#endif /* !SOCKET_H_ */
