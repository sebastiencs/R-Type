//
// BonusMalus.cpp for epitech in /home/bresci_b/R-Type
//
// Made by bresci_b
// Login   <bresci_b@epitech.eu>
//
// Started on  Fri Nov 13 00:37:48 2015 bresci_b
// Last update Fri Nov 13 00:37:48 2015 bresci_b
//

#include "BonusMalus.hh"

BonusMalus::BonusMalus()
  : Object()
{
  _type = 0;
  _speed = 0;
  DEBUG_MSG("BonusMalus created");
}

BonusMalus::BonusMalus(const uint8_t id, const uint8_t type, const uint8_t speed, const uint16_t x, const uint16_t y)
  : Object(id, x, y, 0, 0)
{
  _type = type;
  _speed = speed;
  DEBUG_MSG("BonusMalus created");
}

BonusMalus::~BonusMalus()
{
  DEBUG_MSG("BonusMalus deleted");
}

uint8_t		BonusMalus::getSpeed() const
{
  return _speed;
}

void		BonusMalus::setSpeed(const uint8_t speed)
{
  _speed = speed;
}

uint8_t		BonusMalus::getType() const
{
  return _type;
}

void		BonusMalus::setType(const uint8_t type)
{
  _type = type;
}
