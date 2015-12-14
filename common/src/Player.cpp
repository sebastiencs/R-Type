//
// Player.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Fri Nov 13 00:37:48 2015 chapui_s
// Last update Fri Nov 13 00:37:48 2015 chapui_s
//

#include "Debug.hh"
#include "Player.hh"

Player::Player()
  : Object(),
    _name(""),
    _level(0),
    _life(100),
    _addr(),
    _ready(false)
{
  DEBUG_MSG("Player created");
}

Player::Player(const std::string &name, uint8_t id,
	       const Position &pos = Position(),
	       uint8_t level = 0, int life = 100, bool ready = false)
  : Object(id, pos),
    _name(name),
    _level(level),
    _life(life),
    _addr(),
    _ready(ready)
{
  DEBUG_MSG("Player created");
}

Player::Player(const std::string &name, uint8_t id, uint8_t level, const Addr &addr,
	       const uint16_t sizeX, const uint16_t sizeY)
  : Object(id, 0, 0, sizeX, sizeY),
    _name(name),
    _level(level),
    _life(0),
    _addr(addr),
    _ready(false)
{
  DEBUG_MSG("Player created");
}

Player::~Player()
{
  DEBUG_MSG("Player deleted");
}

const std::list<Position> &Player::getBullets() const
{
	return _bullets;
}

std::list<Position> &Player::getBullets()
{
	return _bullets;
}

void Player::addBullet(Position &bullet)
{
	_bullets.emplace_back(bullet);
}

void Player::addBullet(Position &&bullet)
{
	_bullets.emplace_back(bullet);
}

uint8_t			Player::getLevel() const
{
  return (_level);
}

void			Player::setLevel(uint8_t level)
{
  _level = level;
}

int			Player::getLife() const
{
  return (_life);
}

void			Player::setLife(int life)
{
  _life = life;
}

const std::string	&Player::getName() const
{
  return (_name);
}

void			Player::setName(const std::string &name)
{
  _name = name;
}

const bool		&Player::getReady() const
{
	return (_ready);
}

void			Player::setReady(const bool &ready)
{
	_ready = ready;
}

const Addr		&Player::addr() const
{
  return (_addr);
}

Addr			&Player::addr()
{
  return (_addr);
}

std::ostream &operator<<(std::ostream &os, const Player &p)
{
  auto &pos = p.getPosition();

  os << "Player = { name : '" << p.getName().c_str()
     << "', id : " << (int)p.getID()
     << "', life : " << (int)p.getLife()
     << ", level : " << (int)p.getLevel()
     << ", X : " << (int)pos.x
     << ", Y : " << (int)pos.y
     << " };";
  return (os);
}
