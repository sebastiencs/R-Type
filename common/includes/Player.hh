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
  uint16_t	_level;
  int		_life;
  uint16_t	_id;
  Addr		_addr;

public:
  Player();
  Player(const std::string &, uint16_t, const Position &, uint16_t, int);
  Player(const std::string &name, uint16_t id, uint16_t level, const Addr &);
virtual ~Player();

  virtual const Position	&getPosition() const;
  virtual void			setPosition(const Position &);

  virtual uint16_t		getLevel() const;
  virtual void			setLevel(uint16_t);

  virtual int			getLife() const;
  virtual void			setLife(int);

  virtual uint16_t		getID() const;
  virtual void			setID(uint16_t);

  virtual const std::string	&getName() const;
  virtual void			setName(const std::string &);
  virtual socket_t		socket() const;
};

#endif /* !PLAYER_H_ */
