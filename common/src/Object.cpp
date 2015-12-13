//
// Object.cpp for epitech in /home/bresci_b/R-Type
//
// Made by bresci_b
// Login   <bresci_b@epitech.eu>
//
// Started on  Fri Nov 13 00:37:48 2015 bresci_b
// Last update Fri Nov 13 00:37:48 2015 bresci_b
//

# include "Object.hh"

Object::Object()
{
  DEBUG_MSG("Object created");
}

Object::Object(const uint16_t posX, const uint16_t posY, const uint8_t sizeX, const uint8_t sizeY)
  : _posX(posX),
    _posY(posY),
    _sizeX(sizeX),
    _sizeY(sizeY)
{
  DEBUG_MSG("Object created");
}

Object::~Object()
{
  DEBUG_MSG("Object deleted");
}

void		Object::setX(const uint16_t posX)
{
  _posX = posX;
}

void		Object::setY(const uint16_t posY)
{
  _posY = posY;
}

void		Object::setSizeX(const uint8_t sizeX)
{
  _sizeX = sizeX;
}

void		Object::setSizeY(const uint8_t sizeY)
{
  _sizeY = sizeY;
}

uint16_t	Object::getX() const
{
  return _posX;
}

uint16_t	Object::getY() const
{
  return _posY;
}

uint8_t		Object::getSizeX() const
{
  return _sizeX;
}

uint8_t		Object::getSizeY() const
{
  return _sizeY;
}
