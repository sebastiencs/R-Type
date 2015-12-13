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
  : Object(0, 0, 0, 0, 0),
    _life(0),
    _type(0)
{
  DEBUG_MSG("Enemy created");
}

Enemy::Enemy(const uint8_t id, const int life, const uint8_t type)
  : Object(id, Tools::random(1, 1024), Tools::random(1, 768), 0, 0),
    _life(life),
    _type(type),
    _status(JUST_ENTERED)
{
  if (type == 0) {
    _sizeX = 70;
    _sizeY = 50;
  }
  DEBUG_MSG("Enemy created");
}

Enemy::Enemy(const uint8_t id, const int life, const uint8_t type, const uint16_t x, const uint16_t y)
  : Object(id, x, y, 0, 0),
    _life(life),
    _type(type),
    _status(JUST_ENTERED)
{
  if (type == 0) {
    _sizeX = 70;
    _sizeY = 50;
  }
  DEBUG_MSG("Enemy created");
}

Enemy::~Enemy()
{
  DEBUG_MSG("Enemy deleted");
}

void	Enemy::setLife(const int life)
{
  _life = life;
}

void	Enemy::setType(const uint8_t type)
{
  _type = type;
}

int	Enemy::getLife() const
{
  return _life;
}

uint8_t	Enemy::getType() const
{
  return _type;
}

int	Enemy::getStatus() const
{
  return (_status);
}

void	Enemy::setStatus(const int status)
{
  _status = status;
}

void	Enemy::pushAction(int action)
{
  _actions.push(action);
}

void	Enemy::nextAction()
{
  int action = UNDEFINED;

  if (_actions.size()) {
    action = _actions.front();
    _actions.pop();

  }
  _status = action;
}
