
#include "PaquetObstacle.hh"

PaquetObstacle::PaquetObstacle()
	: _id(Paquet::OBSTACLE)
{
}

PaquetObstacle::PaquetObstacle(void *data, size_t len)
{
	size_t	ptr = 0;

	writeData<char>(ptr, reinterpret_cast<const char *>(data), len);
}

PaquetObstacle::~PaquetObstacle()
{
}

void PaquetObstacle::setType(const uint8_t& type)
	{_type = type;}

void PaquetObstacle::setPosition(const uint8_t& x, const uint8_t& y)
{
	_x = x;
	_y = y;
}

const uint8_t & PaquetObstacle::getType() const
	{return _type;}

const uint8_t & PaquetObstacle::getX() const
	{return _x;}

const uint8_t & PaquetObstacle::getY() const
	{return _y;}

void			PaquetObstacle::parsePaquet()
{
	size_t	ptr = 0;

	_id = readData<uint8_t>(ptr);
	_type = readData<uint8_t>(ptr);
	_x = readData<uint8_t>(ptr);
	_y = readData<uint8_t>(ptr);
}

void			PaquetObstacle::createPaquet()
{
	size_t	ptr = 0;

	writeData<uint8_t>(ptr, &_id);
	writeData<uint8_t>(ptr, &_type);
	writeData<uint8_t>(ptr, &_x);
	writeData<uint8_t>(ptr, &_y);
}

std::ostream	&operator<<(std::ostream &os, PaquetObstacle &p)
{
	p.parsePaquet();
	os << "PaquetObstacle = " << std::endl
		<< " { Obstacle type: " << p.getType()
		<< ", Position: [" << p.getX() << " - " << p.getY() << "]"
		<< " };" << std::endl;
	return (os);
}
