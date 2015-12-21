#include "PaquetEnemy.hh"

PaquetEnemy::PaquetEnemy()
  : _id(Paquet::ENEMY)
{
}

PaquetEnemy::PaquetEnemy(const Buffer &buf)
{
  size_t	ptr = 0;

  writeData(ptr, buf.get(), buf.size());
  parsePaquet();
}

PaquetEnemy::~PaquetEnemy()
{
}

void	PaquetEnemy::setType(const uint8_t type)
{
  _type = type;
}

void	PaquetEnemy::setID(const uint8_t id)
{
  _eID = id;
}

void	PaquetEnemy::setPosition(const uint16_t x, const uint16_t y)
{
  _x = x;
  _y = y;
}

void	PaquetEnemy::setLife(const uint8_t life)
{
  _life = life;
}

uint8_t  PaquetEnemy::getType() const
{
  return _type;
}

uint8_t  PaquetEnemy::getID() const
{
  return _eID;
}

uint16_t  PaquetEnemy::getX() const
{
  return _x;
}

uint16_t  PaquetEnemy::getY() const
{
  return _y;
}

uint8_t  PaquetEnemy::getLife() const
{
  return _life;
}

void			PaquetEnemy::parsePaquet()
{
  size_t	ptr = 0;

  _id = readData<uint8_t>(ptr);
  _type = readData<uint8_t>(ptr);
  _eID = readData<uint8_t>(ptr);
  _x = readData<uint16_t>(ptr);
  _y = readData<uint16_t>(ptr);
  _life = readData<uint8_t>(ptr);
}

void			PaquetEnemy::createPaquet()
{
  size_t	ptr = 0;

  writeData<uint8_t>(ptr, &_id);
  writeData<uint8_t>(ptr, &_type);
  writeData<uint8_t>(ptr, &_eID);
  writeData<uint16_t>(ptr, &_x);
  writeData<uint16_t>(ptr, &_y);
  writeData<uint8_t>(ptr, &_life);
}

std::ostream	&operator<<(std::ostream &os, PaquetEnemy &p)
{
  p.parsePaquet();
  os << "PaquetEnemy = "
     << " { Type : " << (int)p.getType()
     << ", ID : " << (int)p.getID()
     << ", Position: [" << (int)p.getX() << " - " << (int)p.getY() << "]"
     << ", Life : " << (int)p.getLife()
     << " };";
  return (os);
}
