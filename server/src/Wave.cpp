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
    case 2: // 2 normal
    case 3:
      {
	while (++i < 2) {
	  auto e = std::make_shared<Enemy>(_party.getUniqueID(), 100, Enemy::NORMAL, 1000, 400 + i * 200);
	  e->pushAction(Enemy::FOLLOWING);
	  e->setColumn(700 + i * 100);
	  _party.addEnemy(e);
	}
	break;
      }
    case 4: // 4 mid normal
    case 6:
    case 7:
      {
	while (++i < 4) {
	  auto e = std::make_shared<Enemy>(_party.getUniqueID(), 120, Enemy::MID_NORMAL, 1000, 300 + i * 100);
	  e->pushAction(Enemy::FOLLOWING);
	  e->setColumn(600 + i * 100);
	  _party.addEnemy(e);
	}
	break;
      }
    case 5: // 1 mini boss
      {
	auto e = std::make_shared<Enemy>(_party.getUniqueID(), 250, Enemy::MID_BOSS, 1000, 400);
	e->pushAction(Enemy::FOLLOWING);
	e->setColumn(700);
	_party.addEnemy(e);
	break;
      }
    case 8: // 1 boss
      {
	auto e = std::make_shared<Enemy>(_party.getUniqueID(), 350, Enemy::BOSS, 1000, 400);
	e->pushAction(Enemy::FOLLOWING);
	e->setColumn(700);
	_party.addEnemy(e);
	break;
      }
    case 10: // 2 mini boss
      {
	while (++i < 2) {
	  auto e = std::make_shared<Enemy>(_party.getUniqueID(), 250, Enemy::MID_BOSS, 1000, 200 + i * 220);
	  e->pushAction(Enemy::FOLLOWING);
	  e->setColumn(600 + i * 100);
	  _party.addEnemy(e);
	}
	break;		  
      }
    case 12: // 5 mid normal
      {
	while (++i < 5) {
	  auto e = std::make_shared<Enemy>(_party.getUniqueID(), 120, Enemy::MID_NORMAL, 1000, 120 + i * 100);
	  e->pushAction(Enemy::FOLLOWING);
	  e->setColumn(600 + i * 100);
	  _party.addEnemy(e);
	}
	break;
      }
    case 13: // 2 boss
      {
	while (++i < 2) {
	  auto e = std::make_shared<Enemy>(_party.getUniqueID(), 350, Enemy::BOSS, 1000, 200 + i * 220);
	  e->pushAction(Enemy::FOLLOWING);
	  e->setColumn(600 + i * 100);
	  _party.addEnemy(e);
	}
	break;		  
      }
    case 15: // 1 boss 1 mid boss 1 mid normal
      {
	auto e = std::make_shared<Enemy>(_party.getUniqueID(), 250, Enemy::MID_BOSS, 1000, 180);
	e->pushAction(Enemy::FOLLOWING);
	e->setColumn(700);
	_party.addEnemy(e);
	e = std::make_shared<Enemy>(_party.getUniqueID(), 120, Enemy::MID_NORMAL, 1000, 400);
	e->pushAction(Enemy::FOLLOWING);
	e->setColumn(700);
	_party.addEnemy(e);
	e = std::make_shared<Enemy>(_party.getUniqueID(), 350, Enemy::BOSS, 1000, 600);
	e->pushAction(Enemy::FOLLOWING);
	e->setColumn(700);
	_party.addEnemy(e);

      }
    default: // 1 normal defaut
      {
	auto e = std::make_shared<Enemy>(_party.getUniqueID(), 100, Enemy::NORMAL, 1000, 400);
	e->pushAction(Enemy::FOLLOWING);
	e->setColumn(700);
	_party.addEnemy(e);
	break;
      }
  }
  i = -1;
  _nbWaveEnemy++;
  if (_nbWaveEnemy > 16)
    _nbWaveEnemy = 0;
}

void		Wave::getSpawnBonusMalus()
{
  switch(_nbWaveBonusMalus)
    {
    case 1:
    case 2:
    case 3:
    case 5:
    case 7:
    case 9:
      {
    	_party.addBonusMalus(std::make_shared<BonusMalus>(_party.getUniqueID(), BonusMalus::LIFE, 100, 500, 500));
    	break;
      }
    case 4:
    case 6:
    case 8:
    case 10:
    default:
      {
	_party.addBonusMalus(std::make_shared<BonusMalus>(_party.getUniqueID(), BonusMalus::TRIPLE_SHOT, 100, 500, 500));
	break;
      }
    }
  _nbWaveBonusMalus++;
  if (_nbWaveBonusMalus > 10) {
    _nbWaveBonusMalus = 0;
  }
}
