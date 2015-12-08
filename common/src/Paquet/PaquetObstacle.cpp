
#include "PaquetObstacle.hh"

PaquetObstacle::PaquetObstacle()
	: _id(Paquet::OBSTACLE)
{
}

PaquetObstacle::PaquetObstacle(const Buffer &buf)
{
  size_t	ptr = 0;

  writeData<char>(ptr, reinterpret_cast<const char *>(buf.get()), buf.size());
  parsePaquet();
}

PaquetObstacle::~PaquetObstacle()
{
}

void PaquetObstacle::setType(const uint8_t& type)
	{_type = type;}

void PaquetObstacle::setPosition(const uint16_t& x, const uint16_t& y)
{
	_x = x;
	_y = y;
}

const uint8_t & PaquetObstacle::getType() const
	{return _type;}

const uint16_t & PaquetObstacle::getX() const
	{return _x;}

const uint16_t & PaquetObstacle::getY() const
	{return _y;}

void			PaquetObstacle::parsePaquet()
{
	size_t	ptr = 0;

	_id = readData<uint8_t>(ptr);
	_type = readData<uint8_t>(ptr);
	_x = readData<uint16_t>(ptr);
	_y = readData<uint16_t>(ptr);
}

void			PaquetObstacle::createPaquet()
{
	size_t	ptr = 0;

	writeData<uint8_t>(ptr, &_id);
	writeData<uint8_t>(ptr, &_type);
	writeData<uint16_t>(ptr, &_x);
	writeData<uint16_t>(ptr, &_y);
}

std::ostream	&operator<<(std::ostream &os, PaquetObstacle &p)
{
	p.parsePaquet();
	os << "PaquetObstacle = " << std::endl
		<< " { Obstacle type: " << p.getType()
		<< ", Position: [" << p.getX() << " - " << p.getY() << "]"
		<< " };";
	return (os);
}
