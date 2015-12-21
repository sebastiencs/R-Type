//
// PaquetFirstUDP.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Fri Nov 13 21:47:15 2015 chapui_s
// Last update Fri Nov 13 21:47:15 2015 chapui_s
//

#include "PaquetFirstUDP.hh"

PaquetFirstUDP::PaquetFirstUDP()
	: _id(Paquet::FIRST_UDP),
		_playerId(0)
{
}

PaquetFirstUDP::PaquetFirstUDP(const Buffer &buf)
{
  size_t	ptr = 0;

  writeData(ptr, buf.get(), buf.size());;
  parsePaquet();
}

PaquetFirstUDP::~PaquetFirstUDP()
{
}

void PaquetFirstUDP::setId(uint8_t id)
{
	_playerId = id;
}

uint8_t PaquetFirstUDP::getId() const
{
	return _playerId;
}

void			PaquetFirstUDP::parsePaquet()
{
  size_t	ptr = 0;

  _id = readData<uint8_t>(ptr);
	_playerId = readData<uint8_t>(ptr);
}

void			PaquetFirstUDP::createPaquet()
{
  size_t	ptr = 0;

  writeData<uint8_t>(ptr, &_id);
  writeData<uint8_t>(ptr, &_playerId);
}

std::ostream	&operator<<(std::ostream &os, PaquetFirstUDP &p)
{
  p.parsePaquet();

  int		id = p.getId();

  os << "PaquetFirstUDP = {"
     << " _id : '" << id
     << " };";
  return (os);
}
