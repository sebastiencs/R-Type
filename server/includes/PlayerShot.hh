//
// PlayerShot.cpp for epitech in /home/bresci_b/R-Type
//
// Made by bresci_b
// Login   <bresci_b@epitech.eu>
//
// Started on  Wen Dec 02 21:05:16 2015 bresci_b
// Last update Wen Dec 02 21:11:12 2015 bresci_b
//

#ifndef PLAYERSHOT_H_
# define PLAYERSHOT_H_

# include <iostream>
# include "Debug.hh"

class			PlayerShot
{
public:
  PlayerShot();
  PlayerShot(const uint8_t x, const uint8_t y, const uint8_t type, const uint8_t speed, const uint8_t id);
  virtual ~PlayerShot();
  
  void			setX(const uint8_t x);
  void			setY(const uint8_t y);
  void			setType(const uint8_t y);
  void			setSpeed(const uint8_t	speed);
  void			setID(const uint8_t id);
  uint8_t		getX() const;
  uint8_t		getY() const;
  uint8_t		getType() const;
  uint8_t		getSpeed() const;
  uint8_t		getID() const;
  
private:
  uint8_t		_x;
  uint8_t		_y;
  uint8_t		_type;
  uint8_t		_id;
};

#endif /* !PLAYERSHOT_H_ */
