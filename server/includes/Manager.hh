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
# include <memory>
# include "Party.hh"
# include "Semaphore.hh"
# include "Paquets.hh"
# include "Player.hh"
# include "Addr.hh"
# include "PlayerCoord.hh"

typedef std::list<Party *>	PartyList;
typedef std::list<Player *>	PlayerList;

class		INetwork;

class		Manager : public std::enable_shared_from_this<Manager>
{
private:

  PartyList			_parties;
  PlayerList			_pWaiting;
  Semaphore			_sem;
  std::weak_ptr<INetwork>	_network;

public:
  Manager();
  virtual ~Manager();

  std::shared_ptr<Manager>	getPtr();

  void		deletePlayer(const Addr &);
  void		write(const Paquet &, const Addr &);
  void		setNetwork(std::shared_ptr<INetwork>);
  uint8_t	getID() const;

  void		handlePaquet(PaquetFirst *, const Addr &);
  void		handlePaquet(PaquetJoinParty *, const Addr &);
  void		handlePaquet(PaquetCreateParty *, const Addr &);
  void		handlePaquet(PaquetLaunch *, const Addr &);
  void		handlePaquet(PaquetLeave *, const Addr &);
  void		handlePaquet(PaquetListParties *, const Addr &);
  void		handlePaquet(PaquetListPlayers *, const Addr &);
  void		handlePaquet(PaquetObstacle *, const Addr &);
  void		handlePaquet(PaquetPlayerCoord *, const Addr &);
  void		handlePaquet(PaquetPlayerShot *, const Addr &);
  void		handlePaquet(PaquetReady *, const Addr &);
  void		handlePaquet(PaquetRequestParties *, const Addr &);
  void		handlePaquet(PaquetRequestPlayers *, const Addr &);
  void		handlePaquet(PaquetResponse *, const Addr &);
};

#endif /* !MANAGER_H_ */
