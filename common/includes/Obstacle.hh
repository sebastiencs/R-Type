//
// Obstacle.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Mon Dec 14 01:33:22 2015 chapui_s
// Last update Mon Dec 14 01:33:22 2015 chapui_s
//

#ifndef OBSTACLE_H_
# define OBSTACLE_H_

# include "Object.hh"

class		Obstacle : public Object
{
public:
  Obstacle();
  Obstacle(const uint8_t id, const uint16_t x = 0, const uint16_t y = 0, const uint16_t sizeX = 0, const uint16_t sizeY = 0);
  virtual ~Obstacle();
};


#endif /* !OBSTACLE_H_ */
