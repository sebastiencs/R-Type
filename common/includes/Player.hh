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
# include "Addr.hh"
# include "Object.hh"

class		Player : public Object
{
private:
  std::list<Position> _bullets;
  std::string	_name;
  uint8_t	_level;
  int		_life;
  Addr		_addr;
  bool		_ready;

public:
  Player();
  Player(const std::string &, uint8_t, const Position &, uint8_t, int, bool);
  Player(const std::string &name, uint8_t id, uint8_t level, const Addr & = 0, const uint8_t sizeX = 0, const uint8_t sizeY = 0);
  virtual ~Player();

  virtual const std::list<Position> &getBullets() const;
  virtual std::list<Position>	&getBullets();
  virtual void			addBullet(Position &&);
  virtual void			addBullet(Position &);

  virtual uint8_t		getLevel() const;
  virtual void			setLevel(uint8_t);

  virtual int			getLife() const;
  virtual void			setLife(int);

  virtual const std::string	&getName() const;
  virtual void			setName(const std::string &);

  virtual const bool	&getReady() const;
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
