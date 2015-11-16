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
  : _addr()
{
}

Addr::Addr(const struct sockaddr_in &addr)
{
  _addr = addr;
}

Addr::~Addr()
{
}

void				Addr::set(struct sockaddr_in &addr)
{
  _addr = addr;
}

const struct sockaddr_in	&Addr::get() const
{
  return (_addr);
}
