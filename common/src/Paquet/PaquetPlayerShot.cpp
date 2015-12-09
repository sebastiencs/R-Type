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

void PaquetPlayerShot::setType(const uint8_t type)
{
	_type = type;
}

void PaquetPlayerShot::setPlayerID(const uint8_t id)
{
	_playerID = id;
}

void PaquetPlayerShot::setPosition(const uint16_t x, const uint16_t y)
{
	_x = x;
	_y = y;
}

void PaquetPlayerShot::setSpeed(uint8_t speed)
{
	_speed = speed;
}

uint8_t PaquetPlayerShot::getType() const
{
	return _type;
}

uint8_t PaquetPlayerShot::getPlayerID() const
{
	return _playerID;
}

uint16_t PaquetPlayerShot::getX() const
{
	return _x;
}

uint16_t PaquetPlayerShot::getY() const
{
	return _y;
}

uint8_t PaquetPlayerShot::getSpeed() const
{
	return (_speed);
}

void			PaquetPlayerShot::parsePaquet()
{
	size_t	ptr = 0;

	_id = readData<uint8_t>(ptr);
	_playerID = readData<uint8_t>(ptr);
	_x = readData<uint16_t>(ptr);
	_y = readData<uint16_t>(ptr);
	_type = readData<uint8_t>(ptr);
	_speed = readData<uint8_t>(ptr);
}

void			PaquetPlayerShot::createPaquet()
{
	size_t	ptr = 0;

	writeData<uint8_t>(ptr, &_id);
	writeData<uint8_t>(ptr, &_playerID);
	writeData<uint16_t>(ptr, &_x);
	writeData<uint16_t>(ptr, &_y);
	writeData<uint8_t>(ptr, &_type);
	writeData<uint8_t>(ptr, &_speed);
}

std::ostream	&operator<<(std::ostream &os, PaquetPlayerShot &p)
{
	p.parsePaquet();
	os << "PaquetPlayerShot = "
	   << " { PlayerID: " << (int)p.getPlayerID()
	   << ", Shot type: " << (int)p.getType()
	   << ", Position: [" << (int)p.getX() << " - " << (int)p.getY() << "]"
	   << ", Speed: " << (int)p.getSpeed()
	   << " };";
	return (os);
}
