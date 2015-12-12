#include "PaquetBonusMalus.hh"

PaquetBonusMalus::PaquetBonusMalus()
  : _id(Paquet::BONUS_MALUS)
{
}

PaquetBonusMalus::PaquetBonusMalus(const Buffer &buf)
{
  size_t	ptr = 0;

  writeData<char>(ptr, reinterpret_cast<const char *>(buf.get()), buf.size());
  parsePaquet();
}

PaquetBonusMalus::~PaquetBonusMalus()
{
}

void	PaquetBonusMalus::setType(const uint8_t type)
{
  _type = type;
}

void	PaquetBonusMalus::setID(const uint8_t id)
{
  _eID = id;
}

void	PaquetBonusMalus::setPosition(const uint16_t x, const uint16_t y)
{
  _x = x;
  _y = y;
}

void	PaquetBonusMalus::setSpeed(const uint8_t speed)
{
  _speed = speed;
}

uint8_t  PaquetBonusMalus::getType() const
{
  return _type;
}

uint8_t  PaquetBonusMalus::getID() const
{
  return _eID;
}

uint16_t  PaquetBonusMalus::getX() const
{
  return _x;
}

uint16_t  PaquetBonusMalus::getY() const
{
  return _y;
}

uint8_t  PaquetBonusMalus::getSpeed() const
{
  return _speed;
}

void			PaquetBonusMalus::parsePaquet()
{
  size_t	ptr = 0;

  _id = readData<uint8_t>(ptr);
  _type = readData<uint8_t>(ptr);
  _eID = readData<uint8_t>(ptr);
  _x = readData<uint16_t>(ptr);
  _y = readData<uint16_t>(ptr);
  _speed = readData<uint8_t>(ptr);
}

void			PaquetBonusMalus::createPaquet()
{
  size_t	ptr = 0;

  writeData<uint8_t>(ptr, &_id);
  writeData<uint8_t>(ptr, &_type);
  writeData<uint8_t>(ptr, &_eID);
  writeData<uint16_t>(ptr, &_x);
  writeData<uint16_t>(ptr, &_y);
  writeData<uint8_t>(ptr, &_speed);
}

std::ostream	&operator<<(std::ostream &os, PaquetBonusMalus &p)
{
  p.parsePaquet();
  os << "PaquetBonusMalus = "
     << " { Type : " << (int)p.getType()
     << ", ID : " << (int)p.getID()
     << ", Position: [" << (int)p.getX() << " - " << (int)p.getY() << "]"
     << ", Speed : " << (int)p.getSpeed()
     << " };";
  return (os);
}
