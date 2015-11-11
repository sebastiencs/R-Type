//
// SocketUDPWin.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 15:45:54 2015 chapui_s
// Last update Wed Nov 11 15:45:54 2015 chapui_s
//

#include <stdexcept>
#include "SocketUDPWin.hh"

SocketUDPWin::SocketUDPWin(CONNECTION_TYPE type)
{
  DEBUG_MSG("SocketTCPWin created");
}

SocketUDPWin::SocketUDPWin(CONNECTION_TYPE type, socket_t fd)
{
  DEBUG_MSG("SocketTCPWin created");
}

SocketUDPWin::~SocketUDPWin()
{
  DEBUG_MSG("SocketTCPWin deleted");
}

int	SocketUDPWin::connect(const std::string &addr, uint16_t port)
{
  return (0);
}

int	SocketUDPWin::bind(uint16_t port)
{
  return (0);
}

ssize_t	SocketUDPWin::write(const void * data, size_t len)
{
  return (0);
}

ssize_t	SocketUDPWin::read(void *data, size_t len)
{
  return (0);
}
