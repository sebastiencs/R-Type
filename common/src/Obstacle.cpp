//
// Obstacle.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Mon Dec 14 01:34:53 2015 chapui_s
// Last update Mon Dec 14 01:34:53 2015 chapui_s
//

#include "Obstacle.hh"

Obstacle::Obstacle()
  : Object()
{
}

Obstacle::Obstacle(const uint8_t id, const uint16_t x, const uint16_t y, const uint16_t sizeX, const uint16_t sizeY)
  : Object(id, x, y, sizeX, sizeY)
{
}

Obstacle::~Obstacle()
{
}
