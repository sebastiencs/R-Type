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
  PlayerList	_playersWaiting;
  Semaphore	_sem;

public:
  Manager();
  virtual ~Manager();

  void		handlePaquet(const PaquetFirst &);
  void		handlePaquet(const PaquetJoinParty &);
  void		handlePaquet(const PaquetCreateParty &);
  void		handlePaquet(const PaquetLaunch &);
  void		handlePaquet(const PaquetLeave &);
  void		handlePaquet(const PaquetListParties &);
  void		handlePaquet(const PaquetListPlayers &);
  void		handlePaquet(const PaquetObstacle &);
  void		handlePaquet(const PaquetPlayerCoord &);
  void		handlePaquet(const PaquetReady &);
  void		handlePaquet(const PaquetRequestParties &);
  void		handlePaquet(const PaquetRequestPlayers &);
  void		handlePaquet(const PaquetResponse &);
};

#endif /* !MANAGER_H_ */
