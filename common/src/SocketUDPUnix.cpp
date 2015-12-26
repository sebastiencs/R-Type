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

SocketUDPUnix::SocketUDPUnix(const CONNECTION_TYPE type)
  : _error(0),
    _addr(),
    _type(type),
    _isKnown(false)
{
  _fd = ::socket(AF_INET, SOCK_DGRAM, 0);

  if (_fd < 0) {
    DEBUG_MSG("Couldn't create socket");
    _error = 1;
  }
  else {
    DEBUG_MSG("SocketUDPUnix created");
  }
}

SocketUDPUnix::~SocketUDPUnix()
{
  DEBUG_MSG("SocketUDPUnix deleted");
  close(_fd);
}

socket_t	SocketUDPUnix::socket() const
{
  return (_fd);
}

int	SocketUDPUnix::connect(const std::string &addr, const uint16_t port)
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

#ifdef DEBUG
  std::cerr << "Connection UDP to " << inet_ntoa(_addr.sin_addr)
	    << ":" << static_cast<int>(ntohs(_addr.sin_port)) << std::endl;
#endif

  return (0);
}

int	SocketUDPUnix::bind(const uint16_t port)
{
  if (_type == SocketUDPUnix::CLIENT) {
    throw std::runtime_error("Try to bind a socket with a client");
  }
  _addr.sin_family = AF_INET;
  _addr.sin_addr.s_addr = htonl(INADDR_ANY);
  _addr.sin_port = htons(port);
  if (::bind(_fd, reinterpret_cast<struct sockaddr *>(&_addr), sizeof(_addr)) < 0) {
    DEBUG_MSG("bind() UDP failed");
    _error = 1;
    return (-1);
  }
  return (0);
}

ssize_t	SocketUDPUnix::write(const Buffer &buf)
{
  ssize_t	n = 0;

  if (_type == SocketUDPUnix::SERVER) {
    if (_isKnown == false) {
      throw std::runtime_error("Error sendto() unknown client");
    }
    n = sendto(_fd, buf.get(), buf.size(), 0, reinterpret_cast<sockaddr *>(&_addr), sizeof(_addr));
  }
  else {
    n = sendto(_fd, buf.get(), buf.size(), 0, reinterpret_cast<sockaddr *>(&_addr), sizeof(_addr));
  }
  if (n < 0) {
    DEBUG_MSG("sendto() failed");
  }
  return (n);
}

ssize_t	SocketUDPUnix::write(const Buffer &buf, const Addr &addr)
{
  struct sockaddr_in	addrIn = addr.getUDP();
  ssize_t		n = 0;

  n = sendto(_fd, buf.get(), buf.size(), 0, reinterpret_cast<sockaddr *>(&addrIn), sizeof(addrIn));
  if (n < 0) {
    DEBUG_MSG("sendto() failed");
  }
  return (n);
}

ssize_t	SocketUDPUnix::write(const Paquet &paquet)
{
  ssize_t	n = 0;

#ifdef DEBUG
  std::cerr << "Send UDP to " << inet_ntoa(_addr.sin_addr)
	    << ":" << static_cast<int>(ntohs(_addr.sin_port)) << std::endl;
#endif
  if (_type == SocketUDPUnix::SERVER) {
    if (_isKnown == false) {
      throw std::runtime_error("Error sendto() unknown client");
    }
    n = sendto(_fd, paquet.getData(), paquet.getSize(), 0, reinterpret_cast<sockaddr *>(&_addr), sizeof(_addr));
  }
  else {
    n = sendto(_fd, paquet.getData(), paquet.getSize(), 0, reinterpret_cast<sockaddr *>(&_addr), sizeof(_addr));
  }
  if (n < 0) {
    DEBUG_MSG("sendto() failed");
  }
  return (n);
}

ssize_t	SocketUDPUnix::write(const Paquet &paquet, const Addr &addr)
{
  struct sockaddr_in	addrIn = addr.getUDP();
  ssize_t		n = 0;

#ifdef DEBUG
  std::cerr << "Send UDP to " << inet_ntoa(addrIn.sin_addr)
	    << ":" << static_cast<int>(ntohs(addrIn.sin_port)) << std::endl;
#endif
  n = sendto(_fd, paquet.getData(), paquet.getSize(), 0, reinterpret_cast<sockaddr *>(&addrIn), sizeof(addrIn));
  if (n < 0) {
    DEBUG_MSG("sendto() failed");
    perror("sendto");
  }
  return (n);
}

ssize_t	SocketUDPUnix::read(Buffer &buf)
{
  ssize_t	n = 0;
  socklen_t	sizeSock = sizeof(_addr);

  buf.reset();
  if (_type == SocketUDPUnix::SERVER) {
    n = recvfrom(_fd, buf.get(), buf.size(), 0, reinterpret_cast<sockaddr *>(&_addr), &sizeSock);
    if (n >= 0) {
      _isKnown = true;
    }
  }
  else {
    n = recvfrom(_fd, buf.get(), buf.size(), 0, reinterpret_cast<sockaddr *>(&_addr), &sizeSock);
  }
#ifdef DEBUG
  std::cerr << "Read UDP from " << inet_ntoa(_addr.sin_addr)
	    << ":" << static_cast<int>(ntohs(_addr.sin_port)) << std::endl;
#endif
  if (n < 0) {
    DEBUG_MSG("recvfrom() failed");
  }
  else {
    buf.setSize(n);
  }
  return (n);
}

const Addr	SocketUDPUnix::getAddr() const
{
  return (Addr(_addr));
}
