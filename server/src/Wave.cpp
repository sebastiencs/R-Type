//
// Wave.cpp for epitech in /home/bresci_b/R-Type
//
// Made by bresci_b
// Login   <bresci_b@epitech.eu>
//
// Started on  Fri Nov 13 00:37:48 2015 bresci_b
// Last update Fri Nov 13 00:37:48 2015 bresci_b
//

#include "Wave.hh"
#include "Party.hh"

Wave::Wave(Party &party)
  :_party(party)
{
  DEBUG_MSG("Wave created");
}

Wave::~Wave()
{
  DEBUG_MSG("Wave deleted");
}

listEnemies	Wave::getSpawn()
{
  static	int i = 0;
  listEnemies	ennemies;
  Enemy		*enemy = new Enemy(_party.getUniqueID(), 100, 1);

  ennemies.emplace_back(enemy);
  return ennemies;
}
