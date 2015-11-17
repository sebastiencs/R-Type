#include "PaquetPlayerCoord.hh"

PaquetPlayerCoord::PaquetPlayerCoord()
	: _id(Paquet::COORD_PLAYER)
{
}

PaquetPlayerCoord::PaquetPlayerCoord(void *data, size_t len)
{
	size_t	ptr = 0;

	writeData<char>(ptr, reinterpret_cast<const char *>(data), len);
	parsePaquet();
}

PaquetPlayerCoord::PaquetPlayerCoord(const Buffer &buf)
{
	size_t	ptr = 0;

  	writeData<char>(ptr, reinterpret_cast<const char *>(buf.get()), buf.size());
  	parsePaquet();
}

PaquetPlayerCoord::~PaquetPlayerCoord()
{
}

void PaquetPlayerCoord::setPlayerID(const uint8_t& id)
	{_playerID = id;}

void PaquetPlayerCoord::setPosition(const uint8_t& x, const uint8_t& y)
{
	_x = x;
	_y = y;
}

const uint8_t & PaquetPlayerCoord::getPlayerID() const
	{return _playerID;}

const uint8_t & PaquetPlayerCoord::getX() const
	{return _x;}

const uint8_t & PaquetPlayerCoord::getY() const
	{return _y;}

void			PaquetPlayerCoord::parsePaquet()
{
	size_t	ptr = 0;

	_id = readData<uint8_t>(ptr);
	_playerID = readData<uint8_t>(ptr);
	_x = readData<uint8_t>(ptr);
	_y = readData<uint8_t>(ptr);
}

void			PaquetPlayerCoord::createPaquet()
{
	size_t	ptr = 0;

	writeData<uint8_t>(ptr, &_id);
	writeData<uint8_t>(ptr, &_playerID);
	writeData<uint8_t>(ptr, &_x);
	writeData<uint8_t>(ptr, &_y);
}

std::ostream	&operator<<(std::ostream &os, PaquetPlayerCoord &p)
{
	p.parsePaquet();
	os << "PaquetPlayerCoord = " << std::endl
		<< " { Player ID: " << p.getPlayerID()
		<< ", Position: [" << p.getX() << " - " << p.getY() << "]"
		<< " };" << std::endl;
	return (os);
}
