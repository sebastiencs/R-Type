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

class		Object
{
public:
  Object();
  Object(const uint16_t posX, const uint16_t posY, const uint8_t sizeX, const uint8_t sizeY);
  virtual ~Object();
  void		setX(const uint16_t posX);
  void		setY(const uint16_t posY);
  void		setSizeX(const uint8_t sizeX);
  void		setSizeY(const uint8_t sizeY);
  uint16_t	getX() const;
  uint16_t	getY() const;
  uint8_t	getSizeX() const;
  uint8_t	getSizeY() const;
  
private:
  uint16_t	_posX;
  uint16_t	_posY;
  uint8_t	_sizeX;
  uint8_t	_sizeY;
};

#endif /* !OBJECT_HH_ */
