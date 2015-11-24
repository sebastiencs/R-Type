//
// Party.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 10 22:44:37 2015 chapui_s
// Last update Tue Nov 10 22:44:37 2015 chapui_s
//

#include "Party.hh"

Party::Party()
  : _name("Unknwon")
{
  DEBUG_MSG("Party created");
}

Party::Party(const std::string &name)
{
  _name = name;
  DEBUG_MSG("Party created");
}

Party::~Party()
{
  DEBUG_MSG("Party deleted");
}

const listPlayers	&Party::getPlayers() const
{
  return (_players);
}

uint8_t			Party::getNb() const
{
  return (_players.size());
}

const std::string	&Party::getName() const
{
  return (_name);
}

bool			Party::addPlayer(Player *player)
{
  if (_players.size() < 4) {
    _players.push_back(player);
    return (true);
  }
  else {
    return (false);
  }
}
