//
// Party.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 10 22:42:25 2015 chapui_s
// Last update Tue Nov 10 22:42:25 2015 chapui_s
//

#ifndef PARTY_H_
# define PARTY_H_

# include <list>
# include <memory>
# include "Semaphore.hh"
# include "Thread.hh"
# include "Debug.hh"
# include "Player.hh"
# include "Enemy.hh"
# include "BonusMalus.hh"
# include "Wave.hh"
# include "ListSecure.hh"
# include "Timer.hh"

class	Manager;
class	Paquet;

typedef std::shared_ptr<Manager>	Manager_SharedPtr;
typedef std::weak_ptr<Manager>		Manager_WeakPtr;

typedef ListSecure<Player_SharedPtr>	listPlayers;
typedef ListSecure<Enemy_SharedPtr>	listEnemies;
typedef ListSecure<BonusMalus_SharedPtr>	listBonusMalus;

typedef std::unique_ptr<Wave>		Wave_UniquePtr;

class			Party
{
  ISemaphore_UniquePtr	_sem;
  IThread_UniquePtr	_thread;
  Manager_WeakPtr	_manager;
  std::string		_name;
  listPlayers		_players;
  listEnemies		_enemies;
  listBonusMalus	_bonusmalus;
  bool			_running;
  Wave_UniquePtr	_wave;
  ITimer_UniquePtr	_timerBonus;
  ITimer_UniquePtr	_timerBullet;

  void				write(const Paquet &, const Addr &) const;
  const Player_SharedPtr	focusOnClosestPlayer(const uint16_t yEnnemy) const;
  void				updateEnemy(const Enemy_SharedPtr &);
  void				updateBonus(const BonusMalus_SharedPtr &);

public:
  Party(const Manager_SharedPtr &&);
  Party(const Manager_SharedPtr &&, const std::string &);
  virtual ~Party();

  void			run();
  void			stop();
  const listPlayers	&getPlayers() const;
  uint8_t		getNb() const;
  const std::string	&getName() const;
  bool			addPlayer(const Player_SharedPtr);
  void			deletePlayer(const Addr &);
  Player_SharedPtr	playerLeave(const uint8_t id);
  bool			isPlayer(const Addr &) const;
  uint8_t		getIdFromAddr(const Addr &) const;
  bool			isPlayer(const uint8_t id) const;
  void			setCoordPlayer(const uint8_t id, const uint16_t x, const uint16_t y);
  void			setReady(const uint8_t id, const uint8_t status);
  void			setPlayerShot(const uint8_t id, const uint16_t x, const uint16_t y, const uint16_t speed, const uint8_t type);
  bool			isRunning() const;
  void			setRunning(const bool);
  bool			addEnemy(const Enemy_SharedPtr &enemy);
  uint8_t		getUniqueID() const;
  bool			addBonusMalus(const BonusMalus_SharedPtr &bm);
  void			broadcast(const listPlayers &, const Paquet &);
  void			broadcast_nolock(const listPlayers &, const Paquet &);
  void			renamePlayer(const uint8_t id, const std::string &&name);
};

typedef std::shared_ptr<Party>	Party_SharedPtr;

#endif /* !PARTY_H_ */
