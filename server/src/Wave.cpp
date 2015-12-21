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
  : _party(party), _nbWaveEnemy(0)
{
  DEBUG_MSG("Wave created");
}

Wave::~Wave()
{
  DEBUG_MSG("Wave deleted");
}

void		Wave::getSpawnEnemy()
{
  int	        i = -1;

  // Faire spawn les ennemies la ou y'a personne

  switch(_nbWaveEnemy)
    {
    case 2: // 2 enemies
      {
	while (++i < 2) {
	  auto e = new Enemy(_party.getUniqueID(), 100, 0, 1000, 400 + i * 200);
	  e->pushAction(Enemy::FOLLOWING);
	  _party.addEnemy(e);
	}
	break;
      }
    case 4: // 4 enemies
      {
	while (++i < 4) {
	  auto e = new Enemy(_party.getUniqueID(), 100, 0, 1000, 300 + i * 100);
	  e->pushAction(Enemy::FOLLOWING);
	  _party.addEnemy(e);
	}
	break;
      }
    case 5: // 1 mini boss
      {
	auto e = new Enemy(_party.getUniqueID(), 200, 1, 1000, 400);
	e->pushAction(Enemy::FOLLOWING);
	_party.addEnemy(e);
	break;
      }
    case 8: // 1 boss
      {
	auto e  = new Enemy(_party.getUniqueID(), 250, 2, 1000, 400);
	e->pushAction(Enemy::FOLLOWING);
	_party.addEnemy(e);
	break;
      }
    default: // 1 enemy par defaut
      {
	auto e = new Enemy(_party.getUniqueID(), 100, 0, 1000, 400);
	e->pushAction(Enemy::FOLLOWING);
	_party.addEnemy(e);
	break;
      }
  }
  i = -1;
  _nbWaveEnemy++;
}

void		Wave::getSpawnBonusMalus()
{
  static int	nb_waves = 0;

  switch(nb_waves)
    {
    case 5:
      {
	_party.addBonusMalus(new BonusMalus(1, 2, 1000, 300));
	break;
      }
    case 10:
      {
	_party.addBonusMalus(new BonusMalus(1, 4, 1000, 400));
	break;
      }
    case 15:
      {
	_party.addBonusMalus(new BonusMalus(1, 8, 1000, 500));
	break;
      }
    case 20:
      {
	_party.addBonusMalus(new BonusMalus(1, 16, 1000, 600));
	break;
      }
    }
  nb_waves++;
}
