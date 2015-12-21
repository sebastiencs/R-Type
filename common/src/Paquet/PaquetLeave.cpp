//
// PaquetLeave.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 15 23:02:55 2015 chapui_s
// Last update Sun Nov 15 23:02:55 2015 chapui_s
//

#include "PaquetLeave.hh"

PaquetLeave::PaquetLeave()
  : _id(Paquet::LEAVE)
{
}

PaquetLeave::PaquetLeave(const Buffer &buf)
{
  size_t	ptr = 0;

  writeData(ptr, buf.get(), buf.size());
  parsePaquet();
}

PaquetLeave::~PaquetLeave()
{
}

void			PaquetLeave::setID(uint8_t id)
{
  _playerID = id;
}

uint8_t		PaquetLeave::getID() const
{
  return (_playerID);
}

void			PaquetLeave::parsePaquet()
{
  size_t	ptr = 0;

  _id = readData<uint8_t>(ptr);
  _playerID = readData<uint8_t>(ptr);
}

void			PaquetLeave::createPaquet()
{
  size_t	ptr = 0;

  writeData<uint8_t>(ptr, &_id);
  writeData<uint8_t>(ptr, &_playerID);
}

std::ostream	&operator<<(std::ostream &os, PaquetLeave &p)
{
  p.parsePaquet();

  int		playerID = p.getID();

  os << "PaquetLeave = { player ID : " << playerID << " };";
  return (os);
}
