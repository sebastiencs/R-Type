//
// Bullet.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Mon Dec 14 01:41:47 2015 chapui_s
// Last update Mon Dec 14 01:41:47 2015 chapui_s
//

#include "Bullet.hh"

Bullet::Bullet()
  : Object()
{
  _speed = 0;
  _type = 0;
  DEBUG_MSG("Bullet created");
}

Bullet::Bullet(const uint16_t x, const uint16_t y, const uint16_t speed, const uint8_t type, const uint16_t sizeX, const uint16_t sizeY)
  : Object(0, x, y, sizeX, sizeY)
{
  _type = type;
  _speed = speed;
  DEBUG_MSG("Bullet created");
}

Bullet::~Bullet()
{
  DEBUG_MSG("Bullet deleted");
}

uint16_t	Bullet::getSpeed() const
{
  return (_speed);
}

void		Bullet::setSpeed(const uint16_t speed)
{
  _speed = speed;
}

uint8_t		Bullet::getType() const
{
  return _type;
}

void		Bullet::setType(const uint8_t type)
{
  _type = type;
}
