//
// SocketUDPUnix.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 10:32:56 2015 chapui_s
// Last update Wed Nov 11 10:32:56 2015 chapui_s
//

#include <stdexcept>
#include <netdb.h>
#include "SocketUDPUnix.hh"

SocketUDPUnix::SocketUDPUnix(CONNECTION_TYPE type)
  : _error(0),
    _addr(),
    _clientAddr(),
    _type(type)
{
  _fd = socket(AF_INET, SOCK_DGRAM, 0);

  if (_fd < 0) {
    DEBUG_MSG("Couldn't create socket");
    _error = 1;
  }
  else {
    DEBUG_MSG("SocketUDPUnix created");
  }
}

SocketUDPUnix::SocketUDPUnix(CONNECTION_TYPE type, socket_t fd)
  : _fd(fd),
    _error(0),
    _addr(),
    _clientAddr(),
    _type(type)
{
  DEBUG_MSG("SocketUDPUnix created");
}

SocketUDPUnix::~SocketUDPUnix()
{
  DEBUG_MSG("SocketUDPUnix deleted");
  close(_fd);
}

int	SocketUDPUnix::connect(const std::string &addr, uint16_t port)
{
  struct hostent	*h;

  if (_type == SocketUDPUnix::SERVER) {
    throw std::runtime_error("Try to set a dest with a server");
  }

  if (!(h = gethostbyname(addr.c_str()))) {
    DEBUG_MSG("gethostbyname failed");
    _error = 1;
    return (-1);
  }

  _addr.sin_addr = *reinterpret_cast<struct in_addr *>(h->h_addr_list[0]);
  _addr.sin_family = AF_INET;
  _addr.sin_port = htons(port);
  return (0);
}

int	SocketUDPUnix::bind(uint16_t port)
{
  if (_type == SocketUDPUnix::CLIENT) {
    throw std::runtime_error("Try to bind a socket with a client");
  }
  _addr.sin_family = AF_INET;
  _addr.sin_addr.s_addr = INADDR_ANY;
  _addr.sin_port = htons(port);
  if (::bind(_fd, reinterpret_cast<struct sockaddr *>(&_addr), sizeof(_addr)) == -1) {
    DEBUG_MSG("bind() failed");
    _error = 1;
    return (-1);
  }
  return (0);
}

ssize_t	SocketUDPUnix::write(const void * data, size_t len)
{
  ssize_t	n = 0;

  if (_type == SocketUDPUnix::SERVER) {
    n = sendto(_fd, data, len, 0, reinterpret_cast<sockaddr *>(&_clientAddr), sizeof(_clientAddr));
  }
  else {
    n = sendto(_fd, data, len, 0, reinterpret_cast<sockaddr *>(&_addr), sizeof(_addr));
  }
  if (n < 0) {
    DEBUG_MSG("sendto() failed");
  }
  return (n);
}

ssize_t	SocketUDPUnix::read(void *data, size_t len)
{
  ssize_t	n = 0;
  socklen_t	sizeSock = sizeof(_clientAddr);

  if (_type == SocketUDPUnix::SERVER) {
    n = recvfrom(_fd, data, len, 0, reinterpret_cast<sockaddr *>(&_clientAddr), &sizeSock);
  }
  else {
    n = recvfrom(_fd, data, len, 0, reinterpret_cast<sockaddr *>(&_addr), &sizeSock);
  }
  if (n < 0) {
    DEBUG_MSG("recvfrom() failed");
  }
  return (n);
}
