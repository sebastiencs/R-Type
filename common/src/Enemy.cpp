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

Enemy::Enemy()
  : _id(0),
    _x(0),
    _y(0),
    _life(100)
{
    DEBUG_MSG("Enemy created");
}

Enemy::Enemy(const uint8_t id, int life = 100)
  : _id(id),
    _x(std::rand() % 1024),
    _y(std::rand() % 768),
    _life(life)
{
  //1024, 768
  DEBUG_MSG("Enemy created");
}

Enemy::~Enemy()
{
  DEBUG_MSG("Enemy deleted");
}

void	Enemy::setPosX(const uint8_t x)
{
  _x = x;
}

void	Enemy::setPosY(const uint8_t y)
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

uint8_t	Enemy::getPosX() const
{
  return _x;
}

uint8_t Enemy::getPosY() const
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
