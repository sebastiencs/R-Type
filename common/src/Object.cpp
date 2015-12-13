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

Object::Object(const uint8_t id, const uint16_t x, const uint16_t y, const uint8_t sizeX, const uint8_t sizeY)
  : _id(id),
    _x(x),
    _y(y),
    _sizeX(sizeX),
    _sizeY(sizeY)
{
  DEBUG_MSG("Object created");
}

Object::~Object()
{
  DEBUG_MSG("Object deleted");
}

void		Object::setX(const uint16_t x)
{
  _x = x;
}

void		Object::setY(const uint16_t y)
{
  _y = y;
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
  return _x;
}

uint16_t	Object::getY() const
{
  return _y;
}

uint8_t		Object::getSizeX() const
{
  return _sizeX;
}

uint8_t		Object::getSizeY() const
{
  return _sizeY;
}

void		Object::setID(const uint8_t id)
{
  _id = id;
}

uint8_t		Object::getID() const
{
  return (_id);
}
