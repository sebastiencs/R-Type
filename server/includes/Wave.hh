//
// Enemy.hh for epitech in /home/bresci_b/R-Type
//
// Made by bresci_b
// Login   <bresci_b@epitech.eu>
//
// Started on  Fri Nov 13 00:37:48 2015 bresci_b
// Last update Fri Nov 13 00:37:48 2015 bresci_b
//

#ifndef WAVE_HH_
# define WAVE_HH_

# include <iostream>
# include "Enemy.hh"
# include "ListSecure.hh"
# include "Debug.hh"

typedef ListSecure<Enemy_SharedPtr>	listEnemies;

class		Party;

class		Wave
{
public:
  Wave(Party &party);
  virtual ~Wave();
  listEnemies	getSpawn();

private:
  Party		&_party;
};

#endif /* !WAVE_HH_ */
