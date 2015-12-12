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

void		Wave::getSpawn()
{
  static	int nb_waves = 0;
  int	        i = 0;

  // Faire spawn les ennemies la ou y'a personne

  switch(nb_waves)
  {
  case 2: // 2 enemies
    while(++i < 2) {
      _party.addEnemy(new Enemy(_party.getUniqueID(), 100, 1, 700, 400 + i * 200));
    }
    break;
  case 4: // 4 enemies
    while(++i < 4) {
      _party.addEnemy(new Enemy(_party.getUniqueID(), 100, 1, 700, 300 + i * 100));
    }
    break;
  case 5: // 1 boss
    _party.addEnemy(new Enemy(_party.getUniqueID(), 250, 2, 700, 400));
    break;
  default: // 1 enemy par defaut
    _party.addEnemy(new Enemy(_party.getUniqueID(), 100, 1, 700, 400));
    break;
  }
  i = 0;
  nb_waves++;
}
