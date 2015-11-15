//
// PaquetReady.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 15 22:54:33 2015 chapui_s
// Last update Sun Nov 15 22:54:33 2015 chapui_s
//

#include "PaquetReady.hh"

PaquetReady::PaquetReady()
  : _id(Paquet::READY)
{
}

PaquetReady::PaquetReady(void *data, size_t len)
{
  size_t	ptr = 0;

  writeData<char>(ptr, reinterpret_cast<const char *>(data), len);
}

PaquetReady::~PaquetReady()
{
}

void			PaquetReady::setID(uint8_t id)
{
  _playerID = id;
}

uint8_t			PaquetReady::getID() const
{
  return (_playerID);
}

void			PaquetReady::parsePaquet()
{
  size_t	ptr = 0;

  _id = readData<uint8_t>(ptr);
  _playerID = readData<uint8_t>(ptr);
}

void			PaquetReady::createPaquet()
{
  size_t	ptr = 0;

  writeData<uint8_t>(ptr, &_id);
  writeData<uint8_t>(ptr, &_playerID);
}

std::ostream	&operator<<(std::ostream &os, PaquetReady &p)
{
  int		playerID = p.getID();

  p.parsePaquet();
  os << "PaquetReady = { playerID : " << playerID << " };" << std::endl;
  return (os);
}
