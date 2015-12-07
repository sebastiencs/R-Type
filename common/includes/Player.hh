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
# include "IPlayer.hh"
# include "Addr.hh"

class		Player : public IPlayer
{
private:
  std::string	_name;
  Position	_position;
  uint8_t	_level;
  int		_life;
  uint8_t	_id;
  Addr		_addr;
  bool		_ready;

public:
  Player();
  Player(const std::string &, uint8_t, const Position &, uint8_t, int, bool);
  Player(const std::string &name, uint8_t id, uint8_t level, const Addr & = 0);
  virtual ~Player();

  virtual const Position	&getPosition() const;
  virtual void			setPosition(const Position &);

  virtual uint8_t		getLevel() const;
  virtual void			setLevel(uint8_t);

  virtual int			getLife() const;
  virtual void			setLife(int);

  virtual uint8_t		getID() const;
  virtual void			setID(uint8_t);

  virtual const std::string	&getName() const;
  virtual void			setName(const std::string &);

  virtual const bool	&getReady() const;
  virtual void			setReady(const bool &);

  virtual const Addr		&addr() const;
  virtual Addr			&addr();
};

#include <memory>
typedef std::shared_ptr<Player>	Player_SharedPtr;
typedef std::unique_ptr<Player>	Player_UniquePtr;
typedef std::weak_ptr<Player>	Player_WeakPtr;

#endif /* !PLAYER_H_ */
