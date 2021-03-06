//
// Addr.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Mon Nov 16 03:52:12 2015 chapui_s
// Last update Mon Nov 16 03:52:12 2015 chapui_s
//

#include "Addr.hh"
#include <iostream>

Addr::Addr()
  : _addr(),
    _addrUDP(),
    _socket(),
    _type(Addr::NONE),
    _port()
{
}

Addr::Addr(const struct sockaddr_in &addr)
  : _socket(),
    _port()
{
  _type = Addr::UDP;
  _addr = addr;
  _addrUDP = addr;
}

Addr::Addr(const socket_t &socket)
  : _addr(),
    _addrUDP(),
    _port()
{
  _type = Addr::TCP;
  _socket = socket;
}

Addr::Addr(const Addr &addr)
{
  _type = addr._type;
  _addr = addr._addr;
  _addrUDP = addr._addrUDP;
  _socket = addr._socket;
  _port = addr._port;
}

Addr::Addr(const socket_t &fd, const struct sockaddr_in &sock, const uint16_t port)
{
  _socket = fd;
  _addr = sock;
  _port = port;
  _addrUDP = sock;
  _addrUDP.sin_port = htons(port);
}

Addr::~Addr()
{
}

Addr				&Addr::operator=(const Addr &o)
{
  _type = o._type;
  _addr = o._addr;
  _addrUDP = o._addrUDP;
  _socket = o._socket;
  _port = o._port;
  return (*this);
}

void				Addr::set(struct sockaddr_in &addr)
{
  _type = Addr::UDP;
  _addr = addr;
}

void				Addr::setPortUDP(uint16_t port)
{
  _addrUDP.sin_port = port;
}

void				Addr::set(const socket_t &socket)
{
  _type = Addr::TCP;
  _socket = socket;
}

const struct sockaddr_in	&Addr::get() const
{
  return (_addr);
}

struct sockaddr_in		&Addr::get()
{
  return (_addr);
}

const struct sockaddr_in	&Addr::getUDP() const
{
  return (_addrUDP);
}

struct sockaddr_in		&Addr::getUDP()
{
  return (_addrUDP);
}

const socket_t			&Addr::getSocket() const
{
  return (_socket);
}

bool				Addr::operator==(const Addr &other) const
{
  return (_socket == other.getSocket());
}

Addr::TypeAddr			Addr::getType() const {
  return (_type);
}

uint16_t			Addr::getPort() const {
  return (_port);
}

std::ostream &operator<<(std::ostream &os, const Addr &o)
{

#ifdef __unix__

  sockaddr_in sock = o.get();

  os << "Addr = { fd : " << (int)o.getSocket()
     << ", sock : "
     << inet_ntoa(sock.sin_addr)
     << ":" << ntohs(sock.sin_port)
     << " };";

#endif

  return (os);
}
