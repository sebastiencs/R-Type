#include "PaquetPlayerShot.hh"

PaquetPlayerShot::PaquetPlayerShot()
	: _id(Paquet::PLAYER_SHOT)
{
}

PaquetPlayerShot::PaquetPlayerShot(const Buffer &buf)
{
	size_t	ptr = 0;

	writeData<char>(ptr, reinterpret_cast<const char *>(buf.get()), buf.size());
	parsePaquet();
}

PaquetPlayerShot::~PaquetPlayerShot()
{
}

void PaquetPlayerShot::setType(const uint8_t& type)
{
	_type = type;
}

void PaquetPlayerShot::setPlayerID(const uint8_t& id)
{
	_playerID = id;
}

void PaquetPlayerShot::setPosition(const uint16_t& x, const uint16_t& y)
{
	_x = x;
	_y = y;
}

const uint8_t & PaquetPlayerShot::getType() const
{
	return _type;
}

const uint8_t & PaquetPlayerShot::getPlayerID() const
{
	return _playerID;
}

const uint16_t & PaquetPlayerShot::getX() const
{
	return _x;
}

const uint16_t & PaquetPlayerShot::getY() const
{
	return _y;
}

void			PaquetPlayerShot::parsePaquet()
{
	size_t	ptr = 0;

	_id = readData<uint8_t>(ptr);
	_type = readData<uint8_t>(ptr);
	_x = readData<uint16_t>(ptr);
	_y = readData<uint16_t>(ptr);
}

void			PaquetPlayerShot::createPaquet()
{
	size_t	ptr = 0;

	writeData<uint8_t>(ptr, &_id);
	writeData<uint8_t>(ptr, &_type);
	writeData<uint16_t>(ptr, &_x);
	writeData<uint16_t>(ptr, &_y);
}

std::ostream	&operator<<(std::ostream &os, PaquetPlayerShot &p)
{
	p.parsePaquet();
	os << "PaquetPlayerShot = " << std::endl
		<< " { PlayerID: " << p.getPlayerID()
		<< ", Shot type: " << p.getType()
		<< ", Position: [" << p.getX() << " - " << p.getY() << "]"
		<< " };";
	return (os);
}
