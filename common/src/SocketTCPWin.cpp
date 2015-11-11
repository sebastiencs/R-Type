//
// SocketTCPWin.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 15:43:03 2015 chapui_s
// Last update Wed Nov 11 15:43:03 2015 chapui_s
//

#include <stdexcept>
#include "SocketTCPWin.hh"

SocketTCPWin::SocketTCPWin(CONNECTION_TYPE type)
{
  DEBUG_MSG("SocketTCPWin created");
}

SocketTCPWin::SocketTCPWin(CONNECTION_TYPE type,
			     socket_t fd)
{
  DEBUG_MSG("SocketTCPWin created");
}

SocketTCPWin::~SocketTCPWin()
{
  DEBUG_MSG("SocketTCPWin deleted");
}

int	SocketTCPWin::connect(const std::string &addr, uint16_t port)
{
  return (0);
}

ISocketTCP	*SocketTCPWin::accept()
{
  return 0;
}

int	SocketTCPWin::bind(uint16_t port)
{
  return (0);
}

int	SocketTCPWin::listen(int max)
{
  return (0);
}

ssize_t	SocketTCPWin::write(const void *data, size_t len)
{
  return (0);
}

ssize_t	SocketTCPWin::read(void *data, size_t len)
{
  return (0);
}
