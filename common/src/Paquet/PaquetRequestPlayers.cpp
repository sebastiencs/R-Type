//
// PaquetRequestPlayers.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 15 02:32:16 2015 chapui_s
// Last update Sun Nov 15 02:32:16 2015 chapui_s
//

#include "PaquetRequestPlayers.hh"

PaquetRequestPlayers::PaquetRequestPlayers()
  : _id(Paquet::REQUEST_PLAYERS)
{
}

PaquetRequestPlayers::PaquetRequestPlayers(const Buffer &buf)
{
  size_t	ptr = 0;

  writeData(ptr, buf.get(), buf.size());
  parsePaquet();
}

PaquetRequestPlayers::~PaquetRequestPlayers()
{
}

void			PaquetRequestPlayers::parsePaquet()
{
  size_t	ptr = 0;

  _id = readData<uint8_t>(ptr);
}

void			PaquetRequestPlayers::createPaquet()
{
  size_t	ptr = 0;

  writeData<uint8_t>(ptr, &_id);
}

std::ostream	&operator<<(std::ostream &os, PaquetRequestPlayers &p)
{
  p.parsePaquet();
  os << "PaquetRequestPlayers = {};";
  return (os);
}
