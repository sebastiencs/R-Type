//
// SocketTCPUnix.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 02:46:48 2015 chapui_s
// Last update Wed Nov 11 02:46:48 2015 chapui_s
//

#include <stdexcept>
#include <netdb.h>
#include "SocketTCPUnix.hh"

SocketTCPUnix::SocketTCPUnix(CONNECTION_TYPE type)
  : _error(0),
    _addr(),
    _type(type)
{
  _socket = ::socket(AF_INET, SOCK_STREAM, 0);

  if (_socket >= 0 && type == SocketTCPUnix::SERVER) {
    int unused = 0;
    if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &unused, sizeof unused)) {
      DEBUG_MSG("setsockopt error");
      perror("->");
    }
  }

  if (_socket < 0) {
    DEBUG_MSG("Couldn't create socket");
    _error = 1;
  }
  else {
    DEBUG_MSG("SocketTCPUnix created");
  }
}

SocketTCPUnix::SocketTCPUnix(CONNECTION_TYPE type,
			     socket_t fd)
  : _socket(fd),
    _error(0),
    _addr(),
    _type(type)
{
  DEBUG_MSG("SocketTCPUnix created");
}

SocketTCPUnix::~SocketTCPUnix()
{
  DEBUG_MSG("SocketTCPUnix deleted");
  close(_socket);
}

socket_t	SocketTCPUnix::socket() const
{
  return (_socket);
}

int	SocketTCPUnix::connect(const std::string &addr, uint16_t port)
{
  if (_type == SocketTCPUnix::SERVER) {
    throw std::runtime_error("Try to connect with a server");
  }

  struct hostent	*h;

  if (!(h = gethostbyname(addr.c_str()))) {
    DEBUG_MSG("gethostbyname failed");
    _error = 1;
    return (-1);
  }
  _addr.sin_addr = *reinterpret_cast<struct in_addr *>(h->h_addr_list[0]);
  _addr.sin_family = AF_INET;
  _addr.sin_port = htons(port);
  if (::connect(_socket, reinterpret_cast<struct sockaddr *>(&_addr), sizeof(_addr)) == -1) {
    DEBUG_MSG("connect failed");
    _error = 1;
    return (-1);
  }
  _error = 0;
  return (0);
}

ISocketTCP	*SocketTCPUnix::accept()
{
  struct sockaddr_in	c_addr;
  size_t		size;
  int			newfd;

  if (_type == SocketTCPUnix::CLIENT) {
    throw std::runtime_error("Try to accept with a client");
  }

  size = sizeof(c_addr);
  newfd = ::accept(_socket,
		   reinterpret_cast<struct sockaddr *>(&c_addr),
		   reinterpret_cast<socklen_t *>(&size));
  if (newfd >= 0)
  {
#ifdef DEBUG
    std::cerr << "Connection from " << inet_ntoa(c_addr.sin_addr)
	      << ":" << static_cast<int>(ntohs(c_addr.sin_port)) << std::endl;
#endif // !DEBUG
  }
  else
  {
    _error = 1;
    DEBUG_MSG("accept failed");
  }
  return (new SocketTCPUnix(_type, newfd));
}

int	SocketTCPUnix::bind(uint16_t port)
{
  if (_type == SocketTCPUnix::CLIENT) {
    throw std::runtime_error("Try to bind a socket with a client");
  }

  _addr.sin_family = AF_INET;
  _addr.sin_addr.s_addr = INADDR_ANY;
  _addr.sin_port = htons(port);
  if (::bind(_socket, reinterpret_cast<struct sockaddr *>(&_addr), sizeof(_addr)) == -1) {
    DEBUG_MSG("bind() failed");
    perror("->");
    _error = 1;
    return (-1);
  }
  return (0);
}

int	SocketTCPUnix::listen(int max)
{
  if (_type == SocketTCPUnix::CLIENT) {
    throw std::runtime_error("Try to listen on a socket with a client");
  }

  if (::listen(_socket, max) == -1) {
    DEBUG_MSG("listen() failed");
    return (-1);
  }
  return (0);
}

ssize_t	SocketTCPUnix::write(const Buffer &buf)
{
  if (_error) {
    DEBUG_MSG("Try to send on an invalid socket");
    return (-1);
  }

  return (::write(_socket, buf.get(), buf.size()));
}

ssize_t	SocketTCPUnix::write(const Buffer &buf, const Addr &addr)
{
  if (_error) {
    DEBUG_MSG("Try to send on an invalid socket");
    return (-1);
  }

  return (::write(addr.getSocket(), buf.get(), buf.size()));
}

ssize_t	SocketTCPUnix::write(const Paquet &paquet)
{
  if (_error) {
    DEBUG_MSG("Try to send on an invalid socket");
    return (-1);
  }

  return (::write(_socket, paquet.getData(), paquet.getSize()));
}

ssize_t	SocketTCPUnix::write(const Paquet &paquet, const Addr &addr)
{
  if (_error) {
    DEBUG_MSG("Try to send on an invalid socket");
    return (-1);
  }

  return (::write(addr.getSocket(), paquet.getData(), paquet.getSize()));
}

ssize_t	SocketTCPUnix::read(Buffer &buf)
{
  ssize_t n;

  buf.reset();
  if (_error) {
    DEBUG_MSG("Try to send on an invalid socket");
    return (-1);
  }

  n = ::read(_socket, buf.get(), buf.size());

  if (n < 0) {
    DEBUG_MSG("read() failed");
  }
  else {
    buf.setSize(n);
  }

  return (n);
}

const Addr	SocketTCPUnix::getAddr() const
{
  return (Addr(_socket));
}
