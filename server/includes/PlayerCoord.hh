//
// PlayerCoord.cpp for epitech in /home/bresci_b/R-Type
//
// Made by bresci_b
// Login   <bresci_b@epitech.eu>
//
// Started on  Wen Dec 02 21:05:16 2015 bresci_b
// Last update Wen Dec 02 21:11:12 2015 bresci_b
//

#ifndef PLAYERCOORD_H_
# define PLAYERCOORD_H_

# include <iostream>
# include "Debug.hh"

class		PlayerCoord
{
public:
  PlayerCoord();
  PlayerCoord(uint16_t x, uint16_t y, uint8_t id);
  virtual ~PlayerCoord();
  
  void		setX(uint16_t x);
  void		setY(uint16_t y);
  void		setID(uint8_t id);
  uint16_t	getX() const;
  uint16_t	getY() const;
  uint8_t	getID() const;

private:
  uint16_t	_x;
  uint16_t	_y;
  uint8_t	_id;
};

#endif /* !PLAYERCOORD_H_ */
