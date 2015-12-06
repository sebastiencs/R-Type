//
// PlayerShot.cpp for epitech in /home/bresci_b/R-Type
//
// Made by bresci_b
// Login   <bresci_b@epitech.eu>
//
// Started on  Wen Dec 02 20:54:14 2015 bresci_b
// Last update Wen Dec 02 21:05:14 2015 bresci_b
//

#include "PlayerShot.hh"

PlayerShot::PlayerShot()
	: _x(0),
	_y(0),
	_type(0),
	_id(0)
{
	DEBUG_MSG("PlayerShot created");
}

PlayerShot::PlayerShot(const uint8_t x, const uint8_t y, const uint8_t type, const uint8_t id)
	: _x(x),
	_y(y),
	_type(type),
	_id(id)
{
	DEBUG_MSG("PlayerShot created");
}

PlayerShot::~PlayerShot() {
	DEBUG_MSG("PlayerShot deleted");
}

void		PlayerShot::setX(const uint8_t x) {
	_x = x;
}

void		PlayerShot::setY(const uint8_t y) {
	_y = y;
}

void		PlayerShot::setType(const uint8_t type) {
	_type = type;
}

void		PlayerShot::setID(const uint8_t id) {
	_id = id;
}

uint8_t		PlayerShot::getX() const {
	return _x;
}

uint8_t		PlayerShot::getY() const {
	return _y;
}

uint8_t		PlayerShot::getType() const {
	return _type;
}

uint8_t		PlayerShot::getID() const {
	return _id;
}