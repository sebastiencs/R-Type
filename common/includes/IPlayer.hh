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

# include <tuple>
# include <iostream>

typedef struct s_position {
  s_position() : x(1), y(1) {}
  s_position(uint16_t _x, uint16_t _y) : x(_x), y(_y) {}
  uint16_t x;
  uint16_t y;
} Position;

class		IPlayer
{
public:
	virtual ~IPlayer() {}

	virtual const Position	&getPosition() const = 0;
	virtual void			setPosition(const Position &) = 0;

	virtual const std::list<Position*>& getBullets() const = 0;
	virtual void			addBullet(Position *) = 0;

	virtual uint8_t		getLevel() const = 0;
	virtual void			setLevel(uint8_t) = 0;

	virtual int			getLife() const = 0;
	virtual void			setLife(int) = 0;

	virtual uint8_t		getID() const = 0;
	virtual void	setID(uint8_t) = 0;

	virtual const std::string	&getName() const = 0;
	virtual void	setName(const std::string &) = 0;
};

#endif /* !IPLAYER_H_ */
