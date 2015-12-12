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
# include "PlayerCoord.hh"
# include "PlayerShot.hh"
# include "Enemy.hh"
# include "Wave.hh"
# include "ListSecure.hh"
# include "Timer.hh"

class	Manager;

typedef std::shared_ptr<Manager>	Manager_SharedPtr;
typedef std::weak_ptr<Manager>		Manager_WeakPtr;

typedef ListSecure<Player_SharedPtr>	listPlayers;
typedef ListSecure<Enemy_SharedPtr>	listEnemies;

typedef std::unique_ptr<Wave>		Wave_UniquePtr;

class			Party
{
  ISemaphore_UniquePtr	_sem;
  IThread_UniquePtr	_thread;
  Manager_WeakPtr	_manager;
  std::string		_name;
  listPlayers		_players;
  listEnemies		_enemies;
  bool			_running;
  Wave_UniquePtr	_wave;
  ITimer_UniquePtr	_timerWave;

public:
  Party(const Manager_SharedPtr &&);
  Party(const Manager_SharedPtr &&, const std::string &);
  virtual ~Party();

  void			run();
  void			stop();
  const listPlayers	&getPlayers() const;
  uint8_t		getNb() const;
  const std::string	&getName() const;
  bool			addPlayer(Player_SharedPtr);
  void			deletePlayer(const Addr &);
  Player_SharedPtr	playerLeave(uint8_t id);
  bool			isPlayer(const Addr &) const;
  uint8_t		getIdFromAddr(const Addr &) const;
  bool			isPlayer(uint8_t id) const;
  void			setCoordPlayer(PlayerCoord *pc);
  void			setReady(uint8_t id, uint8_t status);
  void			setPlayerShot(PlayerShot *ps);
  bool			isRunning() const;
  void			setRunning(bool);
  bool			addEnemy(Enemy *enemy);
  uint8_t		getUniqueID() const;
};

#endif /* !PARTY_H_ */
