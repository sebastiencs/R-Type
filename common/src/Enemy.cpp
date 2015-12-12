//
// Enemy.cpp for epitech in /home/bresci_b/R-Type
//
// Made by bresci_b
// Login   <bresci_b@epitech.eu>
//
// Started on  Fri Nov 13 00:37:48 2015 bresci_b
// Last update Fri Nov 13 00:37:48 2015 bresci_b
//

#include "Enemy.hh"
#include "Tools.hh"

Enemy::Enemy()
  : _id(0),
    _x(0),
    _y(0),
    _life(0),
    _type(0)
{
    DEBUG_MSG("Enemy created");
}

Enemy::Enemy(const uint8_t id, const int life, const uint8_t type)
  : _id(id),
    _x(Tools::random(1, 1024)),
    _y(Tools::random(1, 768)),
    _life(life),
    _type(type)
{
  DEBUG_MSG("Enemy created");
}

Enemy::Enemy(const uint8_t id, const int life, const uint8_t type, const uint16_t x, const uint16_t y)
  : _id(id),
    _x(x),
    _y(y),
    _life(life),
    _type(type)
{
  DEBUG_MSG("Enemy created");
}

Enemy::~Enemy()
{
  DEBUG_MSG("Enemy deleted");
}

void	Enemy::setPosX(const uint16_t x)
{
  _x = x;
}

void	Enemy::setPosY(const uint16_t y)
{
  _y = y;
}

void	Enemy::setID(const uint8_t id)
{
  _id = id;
}

void	Enemy::setLife(const int life)
{
  _life = life;
}

void	Enemy::setType(const uint8_t type)
{
  _type = type;
}

uint16_t Enemy::getPosX() const
{
  return _x;
}

uint16_t Enemy::getPosY() const
{
  return _y;
}

uint8_t	Enemy::getID() const
{
  return _id;
}

int	Enemy::getLife() const
{
  return _life;
}

uint8_t	Enemy::getType() const
{
  return _type;
}
