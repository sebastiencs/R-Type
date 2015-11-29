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
  : _name(""),
    _position(),
    _level(0),
    _life(100),
    _id(0),
    _addr()
{
  DEBUG_MSG("Player created");
}

Player::Player(const std::string &name, uint16_t id,
	       const Position &pos = std::make_tuple(1, 1),
	       uint16_t level = 0, int life = 100)
  : _name(name),
    _position(pos),
    _level(level),
    _life(life),
    _id(id),
    _addr()
{
  DEBUG_MSG("Player created");
}

Player::Player(const std::string &name, uint16_t id, uint16_t level, const Addr &addr)
  : _name(name),
    _position(),
    _level(level),
    _life(0),
    _id(id),
    _addr(addr)
{
  DEBUG_MSG("Player created");
}

Player::~Player()
{
  DEBUG_MSG("Player deleted");
}

const Position		&Player::getPosition() const
{
  return (_position);
}

void			Player::setPosition(const Position &pos)
{
  _position = pos;
}

uint16_t		Player::getLevel() const
{
  return (_level);
}

void			Player::setLevel(uint16_t level)
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

uint8_t			Player::getID() const
{
  return (_id);
}

void			Player::setID(uint16_t id)
{
  _id = id;
}

const std::string	&Player::getName() const
{
  return (_name);
}

void			Player::setName(const std::string &name)
{
  _name = name;
}

const Addr		&Player::addr() const
{
  return (_addr);
}
