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
  virtual ~Enemy();

  void		setPosX(const uint8_t x);
  void		setPosY(const uint8_t y);
  void		setPosID(const uint8_t id);
  void		setLife(const int life);
  void		setType(const uint8_t type);
  void		setID(const uint8_t);
  uint8_t	getPosX() const;
  uint8_t	getPosY() const;
  uint8_t	getID() const;
  int		getLife() const;
  uint8_t       getType() const;

private:
  uint8_t	_id;
  uint8_t	_x;
  uint8_t	_y;
  int		_life;
  uint8_t	_type;
};

typedef std::shared_ptr<Enemy>	Enemy_SharedPtr;

#endif /* !ENEMY_HH_ */
