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
  : _id(0),
    _pos(),
    _sizeX(0),
    _sizeY(0)
{
  DEBUG_MSG("Object created");
}

Object::Object(const uint8_t id, const uint16_t x, const uint16_t y, const uint8_t sizeX, const uint8_t sizeY)
  : _id(id),
    _pos(x, y),
    _sizeX(sizeX),
    _sizeY(sizeY)
{
  DEBUG_MSG("Object created");
}

Object::Object(const uint8_t id, const Position pos, const uint8_t sizeX, const uint8_t sizeY)
  : _id(id),
    _pos(pos),
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
  _pos.x = x;
}

void		Object::setY(const uint16_t y)
{
  _pos.y = y;
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
  return _pos.x;
}

uint16_t	Object::getY() const
{
  return _pos.y;
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

const Position	&Object::getPosition() const
{
  return (_pos);
}

Position	&Object::getPosition()
{
  return (_pos);
}

void		Object::setPosition(const Position &&pos)
{
  _pos = pos;
}

void		Object::setPosition(const Position &pos)
{
  _pos = pos;
}
