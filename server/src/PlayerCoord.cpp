//
// PlayerCoord.cpp for epitech in /home/bresci_b/R-Type
//
// Made by bresci_b
// Login   <bresci_b@epitech.eu>
//
// Started on  Wen Dec 02 20:54:14 2015 bresci_b
// Last update Wen Dec 02 21:05:14 2015 bresci_b
//

#include "PlayerCoord.hh"

PlayerCoord::PlayerCoord()
  : _x(0),
    _y(0),
    _id(0)
{
  DEBUG_MSG("PlayerCoord created");
}

PlayerCoord::PlayerCoord(uint16_t x, uint16_t y, uint8_t id)
  : _x(x),
    _y(y),
    _id(id)
{
  DEBUG_MSG("PlayerCoord created");
}

PlayerCoord::~PlayerCoord() {
  DEBUG_MSG("PlayerCoord deleted");
}

void		PlayerCoord::setX(uint16_t x) {
  _x = x;
}

void		PlayerCoord::setY(uint16_t y) {
  _y = y;
}

void		PlayerCoord::setID(uint8_t id) {
  _id = id;
}

uint16_t	PlayerCoord::getX() const {
  return _x;
}

uint16_t	PlayerCoord::getY() const {
  return _y;
}

uint8_t		PlayerCoord::getID() const {
  return _id;
}
