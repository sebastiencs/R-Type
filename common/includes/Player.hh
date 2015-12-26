//
// Player.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Fri Nov 13 00:35:06 2015 chapui_s
// Last update Fri Nov 13 00:35:06 2015 chapui_s
//

#ifndef PLAYER_H_
# define PLAYER_H_

# include <tuple>
# include <list>
# include <memory>
# include "Addr.hh"
# include "Object.hh"

class Bullet;
typedef std::shared_ptr<Bullet>	Bullet_SharedPtr;

class		Player : public Object
{
private:
  std::list<Bullet_SharedPtr> _bullets;
  std::string	_name;
  uint8_t	_level;
  int		_life;
  Addr		_addr;
  bool		_ready;

public:
  Player();
  Player(const std::string &, const uint8_t, const Position &, const uint8_t, const int, const bool);
  Player(const std::string &name, const uint8_t id, const uint8_t level, const Addr & = 0, const uint16_t sizeX = 80, const uint16_t sizeY = 91);
  virtual ~Player();

  virtual const std::list<Bullet_SharedPtr> &getBullets() const;
  virtual std::list<Bullet_SharedPtr>	&getBullets();
  virtual void			addBullet(Bullet_SharedPtr &&);

  virtual uint8_t		getLevel() const;
  virtual void			setLevel(uint8_t);

  virtual int			getLife() const;
  virtual int			&getLife();
  virtual void			setLife(const int);

  virtual const std::string	&getName() const;
  virtual void			setName(const std::string &);

  virtual const bool		&getReady() const;
  virtual void			setReady(const bool &);

  virtual const Addr		&addr() const;
  virtual Addr			&addr();
};

std::ostream &operator<<(std::ostream &os, const Player &p);

#include <memory>
typedef std::shared_ptr<Player>	Player_SharedPtr;
typedef std::unique_ptr<Player>	Player_UniquePtr;
typedef std::weak_ptr<Player>	Player_WeakPtr;

#endif /* !PLAYER_H_ */
