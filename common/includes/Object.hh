//
// Object.hh for epitech in /home/bresci_b/R-Type
//
// Made by bresci_b
// Login   <bresci_b@epitech.eu>
//
// Started on  Fri Nov 13 00:37:48 2015 bresci_b
// Last update Fri Nov 13 00:37:48 2015 bresci_b
//

#ifndef OBJECT_HH_
# define OBJECT_HH_

# include <iostream>
# include "Debug.hh"

typedef struct s_position {
  s_position() : x(1), y(1) {}
  s_position(uint16_t _x, uint16_t _y) : x(_x), y(_y) {}
  s_position(const s_position &pos) : x(pos.x), y(pos.y) {}
  s_position &operator=(const s_position &pos) { x = pos.x; y = pos.y; return (*this); }
  uint16_t x;
  uint16_t y;
} Position;

class		Object
{
public:
  Object();
  Object(const uint8_t id, const uint16_t posX = 0, const uint16_t posY = 0, const uint16_t sizeX = 0, const uint16_t sizeY = 0);
  Object(const uint8_t id, const Position pos, const uint16_t sizeX = 0, const uint16_t sizeY = 0);
  virtual ~Object();

  void			setX(const uint16_t posX);
  void			setY(const uint16_t posY);
  void			setSizeX(const uint16_t sizeX);
  void			setSizeY(const uint16_t sizeY);
  uint16_t		getX() const;
  uint16_t		&getX();
  uint16_t		getY() const;
  uint16_t		&getY();
  uint16_t		getSizeX() const;
  uint16_t		getSizeY() const;
  void			setID(const uint8_t id);
  uint8_t		getID() const;
  const Position	&getPosition() const;
  Position		&getPosition();
  void			setPosition(const Position &&);
  void			setPosition(const Position &);

protected:
  uint8_t	_id;
  Position	_pos;
  uint16_t	_sizeX;
  uint16_t	_sizeY;
};

#endif /* !OBJECT_HH_ */
