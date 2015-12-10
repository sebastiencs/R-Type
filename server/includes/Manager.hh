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
# include "PlayerShot.hh"
# include "ListSecure.hh"

typedef std::list<Party *>		PartyList;
typedef ListSecure<Player_SharedPtr>	PlayerList;

class	INetwork;

typedef std::shared_ptr<INetwork>	INetwork_SharedPtr;
typedef std::weak_ptr<INetwork>		INetwork_WeakPtr;

typedef std::shared_ptr<Manager>	Manager_SharedPtr;
typedef std::unique_ptr<Manager>	Manager_UniquePtr;
typedef std::weak_ptr<Manager>		Manager_WeakPtr;

class		Manager : public std::enable_shared_from_this<Manager>
{
private:

  PartyList		_parties;
  PlayerList		_pWaiting;
  Semaphore		_sem;
  INetwork_WeakPtr	_network;

public:
  Manager();
  virtual ~Manager();

  Manager_SharedPtr	getPtr();

  void		deletePlayer(const Addr &);
  void		write(const Paquet &, const Addr &);
  void		setNetwork(INetwork_SharedPtr &&);
  uint8_t	getID() const;

  void		handlePaquet(PaquetFirst *, const Addr &);
  void		handlePaquet(PaquetJoinParty *, const Addr &);
  void		handlePaquet(PaquetCreateParty *, const Addr &);
  void		handlePaquet(PaquetLeave *, const Addr &);
  void		handlePaquet(PaquetObstacle *, const Addr &);
  void		handlePaquet(PaquetPlayerCoord *, const Addr &);
  void		handlePaquet(PaquetPlayerShot *, const Addr &);
  void		handlePaquet(PaquetReady *, const Addr &);
  void		handlePaquet(PaquetRequestParties *, const Addr &);
  void		handlePaquet(PaquetRequestPlayers *, const Addr &);
  void		handlePaquet(PaquetResponse *, const Addr &);
  void		handlePaquet(PaquetFirstUDP *, const Addr &);
};

#endif /* !MANAGER_H_ */
