#include "PaquetPlayerCoord.hh"

PaquetPlayerCoord::PaquetPlayerCoord()
	: _id(Paquet::COORD_PLAYER)
{
}

PaquetPlayerCoord::PaquetPlayerCoord(const Buffer &buf)
{
	size_t	ptr = 0;

  	writeData(ptr, buf.get(), buf.size());
  	parsePaquet();
}

PaquetPlayerCoord::~PaquetPlayerCoord()
{
}

void PaquetPlayerCoord::setPlayerID(const uint8_t& id)
	{_playerID = id;}

void PaquetPlayerCoord::setPosition(const uint16_t& x, const uint16_t& y)
{
	_x = x;
	_y = y;
}

const uint8_t & PaquetPlayerCoord::getPlayerID() const
	{return _playerID;}

const uint16_t & PaquetPlayerCoord::getX() const
	{return _x;}

const uint16_t & PaquetPlayerCoord::getY() const
	{return _y;}

void			PaquetPlayerCoord::parsePaquet()
{
	size_t	ptr = 0;

	_id = readData<uint8_t>(ptr);
	_playerID = readData<uint8_t>(ptr);
	_x = readData<uint16_t>(ptr);
	_y = readData<uint16_t>(ptr);
}

void			PaquetPlayerCoord::createPaquet()
{
	size_t	ptr = 0;

	writeData<uint8_t>(ptr, &_id);
	writeData<uint8_t>(ptr, &_playerID);
	writeData<uint16_t>(ptr, &_x);
	writeData<uint16_t>(ptr, &_y);
}

std::ostream	&operator<<(std::ostream &os, PaquetPlayerCoord &p)
{
	p.parsePaquet();
	os << "PaquetPlayerCoord = "
	   << " { Player ID: " << (int)p.getPlayerID()
	   << ", Position: [" << (int)p.getX() << " - " << (int)p.getY() << "]"
	   << " };";
	return (os);
}
