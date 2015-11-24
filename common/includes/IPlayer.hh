//
// IPlayer.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Fri Nov 13 00:23:17 2015 chapui_s
// Last update Fri Nov 13 00:23:17 2015 chapui_s
//

#ifndef IPLAYER_H_
# define IPLAYER_H_

# ifdef __unix__

typedef int	socket_t;

# elif defined(_WIN32)

#  include "ISocketTCP.hh"

# endif

# include <tuple>
# include <iostream>

typedef std::tuple<uint16_t, uint16_t>	Position;

class		IPlayer
{
public:
  virtual ~IPlayer() {};

  virtual const Position	&getPosition() const = 0;
  virtual void			setPosition(const Position &) = 0;

  virtual uint16_t		getLevel() const = 0;
  virtual void			setLevel(uint16_t) = 0;

  virtual int			getLife() const = 0;
  virtual void			setLife(int) = 0;

  virtual uint16_t		getID() const = 0;
  virtual void			setID(uint16_t) = 0;

  virtual const std::string	&getName() const = 0;
  virtual void			setName(const std::string &) = 0;
  virtual socket_t		socket() const = 0;
};

#endif /* !IPLAYER_H_ */
