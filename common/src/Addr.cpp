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

bool				Addr::operator==(const Addr &other)
{
  struct sockaddr_in	o = other.get();
  uint8_t		*ptr = reinterpret_cast<uint8_t *>(&_addr);
  uint8_t		*ptr2 = reinterpret_cast<uint8_t *>(&o);

  return (std::equal(ptr, ptr + sizeof(_addr), ptr2));
}
