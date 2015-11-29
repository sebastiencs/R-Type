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

Addr::Addr()
  : _addr(),
    _socket(),
    _type(Addr::NONE)
{
}

Addr::Addr(const struct sockaddr_in &addr)
  : _socket()
{
  _type = Addr::UDP;
  _addr = addr;
}

Addr::Addr(const socket_t &socket)
  : _addr()
{
  _type = Addr::TCP;
  _socket = socket;
}

Addr::~Addr()
{
}

void				Addr::set(struct sockaddr_in &addr)
{
  _type = Addr::UDP;
  _addr = addr;
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

const socket_t			&Addr::getSocket() const
{
  return (_socket);
}

bool				Addr::operator==(const Addr &other) const
{
  if (_type == Addr::TCP) {
    return (_socket == other.getSocket());
  }
  else {
    const struct sockaddr_in	&o = other.get();

#ifdef __unix__
    return (_addr.sin_addr.s_addr == o.sin_addr.s_addr && _addr.sin_port == o.sin_port);
#elif defined(_WIN32)
    return (_addr.sin_addr.S_un.S_addr == o.sin_addr.S_un.S_addr && _addr.sin_port == o.sin_port);
#endif
  }
}

Addr::TypeAddr			Addr::getType() const {
  return (_type);
}
