//
// Enemy.hh for epitech in /home/bresci_b/R-Type
//
// Made by bresci_b
// Login   <bresci_b@epitech.eu>
//
// Started on  Fri Nov 13 00:37:48 2015 bresci_b
// Last update Fri Nov 13 00:37:48 2015 bresci_b
//

#ifndef ENEMY_HH_
# define ENEMY_HH_

# include <iostream>
# include "Debug.hh"

class		Enemy
{
public:
  Enemy();
  Enemy(const uint8_t id, int life);
  ~Enemy();

  void		setPosX(const uint8_t x);
  void		setPosY(const uint8_t y);
  void		setPosID(const uint8_t id);
  void		setLife(const int life);
  uit8_t	getPosX() const;
  uit8_t	getPosY() const;
  uit8_t	getID() const;
  int		getLife() const;

private:
  uint8_t	_x;
  uint8_t	_y;
  uint8_t	_id;
  int		_life;
};

#endif /* !ENEMY_HH_ */
