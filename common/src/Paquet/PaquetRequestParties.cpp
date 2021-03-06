//
// PaquetRequestParties.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sat Nov 14 04:54:59 2015 chapui_s
// Last update Sat Nov 14 04:54:59 2015 chapui_s
//

#include "PaquetRequestParties.hh"

PaquetRequestParties::PaquetRequestParties()
  : _id(Paquet::REQUEST_PARTIES)
{
}

PaquetRequestParties::PaquetRequestParties(const Buffer &buf)
{
  size_t	ptr = 0;

  writeData(ptr, buf.get(), buf.size());
  parsePaquet();
}

PaquetRequestParties::~PaquetRequestParties()
{
}

void			PaquetRequestParties::parsePaquet()
{
  size_t	ptr = 0;

  _id = readData<uint8_t>(ptr);
}

void			PaquetRequestParties::createPaquet()
{
  size_t	ptr = 0;

  writeData<uint8_t>(ptr, &_id);
}

std::ostream	&operator<<(std::ostream &os, PaquetRequestParties &p)
{
  p.parsePaquet();
  os << "PaquetRequestParties = {};";
  return (os);
}
