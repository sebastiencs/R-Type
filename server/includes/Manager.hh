//
// Manager.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Mon Nov 23 17:47:34 2015 chapui_s
// Last update Mon Nov 23 17:47:34 2015 chapui_s
//

#ifndef MANAGER_H_
# define MANAGER_H_

# include <list>
# include "Party.hh"
# include "Semaphore.hh"
# include "Paquets.hh"
# include "Player.hh"

typedef std::list<Party>	PartyList;
typedef std::list<Player>	PlayerList;

class		Manager
{
private:
  PartyList	_parties;
  PlayerList	_pWaiting;
  Semaphore	_sem;

public:
  Manager();
  virtual ~Manager();

  void		handlePaquet(PaquetFirst *);
  void		handlePaquet(PaquetJoinParty *);
  void		handlePaquet(PaquetCreateParty *);
  void		handlePaquet(PaquetLaunch *);
  void		handlePaquet(PaquetLeave *);
  void		handlePaquet(PaquetListParties *);
  void		handlePaquet(PaquetListPlayers *);
  void		handlePaquet(PaquetObstacle *);
  void		handlePaquet(PaquetPlayerCoord *);
  void		handlePaquet(PaquetReady *);
  void		handlePaquet(PaquetRequestParties *);
  void		handlePaquet(PaquetRequestPlayers *);
  void		handlePaquet(PaquetResponse *);
};

#endif /* !MANAGER_H_ */
