//
// Bullet.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Mon Dec 14 01:40:38 2015 chapui_s
// Last update Mon Dec 14 01:40:38 2015 chapui_s
//

#ifndef BULLET_H_
# define BULLET_H_

# include <memory>
# include "Object.hh"

class		Bullet : public Object
{
private:
  uint16_t	_speed;
  uint8_t	_type;

public:
  Bullet();
  Bullet(const uint16_t x, const uint16_t y, const uint16_t speed, const uint8_t type, const uint16_t sizeX = 0, const uint16_t sizeY = 0);
  virtual ~Bullet();

  uint16_t	getSpeed() const;
  void		setSpeed(const uint16_t speed);
  uint8_t	getType() const;
  void		setType(const uint8_t type);
};

typedef std::shared_ptr<Bullet>	Bullet_SharedPtr;

#endif /* !BULLET_H_ */
