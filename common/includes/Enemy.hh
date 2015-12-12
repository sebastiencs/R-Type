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
# include <memory>
# include "Debug.hh"

class		Enemy
{
public:
  Enemy();
  Enemy(const uint8_t id, const int life, const uint8_t type);
  Enemy(const uint8_t id, const int life, const uint8_t type, const uint16_t x, const uint16_t y);
  virtual ~Enemy();

  void		setPosX(const uint16_t x);
  void		setPosY(const uint16_t y);
  void		setPosID(const uint8_t id);
  void		setLife(const int life);
  void		setType(const uint8_t type);
  void		setID(const uint8_t);
  uint16_t	getPosX() const;
  uint16_t	getPosY() const;
  uint8_t	getID() const;
  int		getLife() const;
  uint8_t       getType() const;

private:
  uint8_t	_id;
  uint16_t	_x;
  uint16_t	_y;
  int		_life;
  uint8_t	_type;
};

typedef std::shared_ptr<Enemy>	Enemy_SharedPtr;

#endif /* !ENEMY_HH_ */
