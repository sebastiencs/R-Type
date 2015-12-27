//
// enemy1.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Dec 27 03:21:58 2015 chapui_s
// Last update Sun Dec 27 03:21:58 2015 chapui_s
//

#include "enemy1.hh"

Enemy1::Enemy1()
{
}

Enemy1::~Enemy1()
{
}

const Enemy_SharedPtr Enemy1::getEnemy() const
{
  return (std::make_shared<Enemy>(0, 100, 2));
}

extern "C" IPlugin	*loadEnemy()
{
  return (new Enemy1());
}
