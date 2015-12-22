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
  : Object(),
    _life(0),
    _type(0),
    _intervalShot(5000),
    _shotSpeed(800),
    _column(700),
    _timer(std::make_shared<Timer>())
{
  DEBUG_MSG("Enemy created");
  _timer->start();
}

Enemy::Enemy(const uint8_t id, const int life, const uint8_t type)
  : Object(id, Tools::random(1, 1024), Tools::random(1, 768)),
    _life(life),
    _type(type),
    _status(JUST_ENTERED),
    _intervalShot(5000),
    _shotSpeed(850),
    _column(700),
    _timer(std::make_shared<Timer>())
{
  if (type == 0) {
    _sizeX = 80;
    _sizeY = 55;
    _intervalShot = 1000;
  }
  else if (type == 1) {
    _sizeX = 100;
    _sizeY = 59;
    _intervalShot = 1000;
  }
  else if (type == 2) {
    _sizeX = 120;
    _sizeY = 91;
    _intervalShot = 1000;
  }
  _timer->start();
  DEBUG_MSG("Enemy created");
}

Enemy::Enemy(const uint8_t id, const int life, const uint8_t type, const uint16_t x, const uint16_t y)
  : Object(id, x, y),
    _life(life),
    _type(type),
    _status(JUST_ENTERED),
    _intervalShot(5000),
    _shotSpeed(850),
    _column(700),
    _timer(std::make_shared<Timer>())
{
  if (type == 0) {
    _sizeX = 80;
    _sizeY = 55;
    _intervalShot = 1000;
  }
  else if (type == 1) {
    _sizeX = 100;
    _sizeY = 59;
    _intervalShot = 1000;
  }
  else if (type == 2) {
    _sizeX = 120;
    _sizeY = 91;
    _intervalShot = 1000;
  }
  _timer->start();
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

int	&Enemy::getLife()
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

const ITimer_SharedPtr &Enemy::timer() const
{
  return (_timer);
}

ITimer_SharedPtr &Enemy::timer()
{
  return (_timer);
}

int		Enemy::getIntervalShot() const
{
  return (_intervalShot);
}

void		Enemy::setIntervalShot(const int inter)
{
  _intervalShot = inter;
}

bool		Enemy::hasToShot()
{
  bool		yes = false;

  if (_timer->ms() >= _intervalShot) {
    yes = true;
    _timer->reset();
  }
  return (yes);
}

uint16_t	Enemy::getShotSpeed() const
{
  return (_shotSpeed);
}

void		Enemy::setShotSpeed(const uint16_t speed)
{
  _shotSpeed = speed;
}

const std::list<Bullet_SharedPtr> &Enemy::getBullets() const
{
	return _bullets;
}

std::list<Bullet_SharedPtr> &Enemy::getBullets()
{
	return _bullets;
}

void Enemy::addBullet(Bullet_SharedPtr &&bullet)
{
  _bullets.push_back(bullet);
}

uint16_t	Enemy::getColumn() const
{
  return (_column);
}

void		Enemy::setColumn(const uint16_t col)
{
  _column = col;
}
