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
# include "ListSecure.hh"

typedef ListSecure<Party_SharedPtr>	PartyList;
typedef ListSecure<Player_SharedPtr>	PlayerList;

class	INetwork;

typedef std::shared_ptr<INetwork>	INetwork_SharedPtr;
typedef std::weak_ptr<INetwork>		INetwork_WeakPtr;

typedef std::shared_ptr<Manager>	Manager_SharedPtr;
typedef std::unique_ptr<Manager>	Manager_UniquePtr;
typedef std::weak_ptr<Manager>		Manager_WeakPtr;

typedef std::shared_ptr<PaquetFirst>		PaquetFirst_SharedPtr;
typedef std::shared_ptr<PaquetFirstUDP>		PaquetFirstUDP_SharedPtr;
typedef std::shared_ptr<PaquetCreateParty>	PaquetCreateParty_SharedPtr;
typedef std::shared_ptr<PaquetJoinParty>	PaquetJoinParty_SharedPtr;
typedef std::shared_ptr<PaquetListParties>	PaquetListParties_SharedPtr;
typedef std::shared_ptr<PaquetListPlayers>	PaquetListPlayers_SharedPtr;
typedef std::shared_ptr<PaquetRequestParties>	PaquetRequestParties_SharedPtr;
typedef std::shared_ptr<PaquetRequestPlayers>	PaquetRequestPlayers_SharedPtr;
typedef std::shared_ptr<PaquetResponse>		PaquetResponse_SharedPtr;
typedef std::shared_ptr<PaquetPlayerCoord>	PaquetPlayerCoord_SharedPtr;
typedef std::shared_ptr<PaquetPlayerShot>	PaquetPlayerShot_SharedPtr;
typedef std::shared_ptr<PaquetObstacle>		PaquetObstacle_SharedPtr;
typedef std::shared_ptr<PaquetLaunch>		PaquetLaunch_SharedPtr;
typedef std::shared_ptr<PaquetReady>		PaquetReady_SharedPtr;
typedef std::shared_ptr<PaquetLeave>		PaquetLeave_SharedPtr;
typedef std::shared_ptr<PaquetEnemy>		PaquetEnemy_SharedPtr;
typedef std::shared_ptr<PaquetBonusMalus>	PaquetBonusMalus_SharedPtr;

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

  const Manager_SharedPtr	getPtr();

  void		deletePlayer(const Addr &);
  void		write(const Paquet &, const Addr &) const;
  void		broadcast(const PlayerList &, const Paquet &) const;
  void		broadcast_nolock(const PlayerList &, const Paquet &) const;
  void		broadcast_except(const PlayerList &, const uint8_t, const Paquet &) const;
  void		setNetwork(const INetwork_SharedPtr &&);
  uint8_t	getID() const;

  void		handlePaquet(const PaquetFirst_SharedPtr &&, const Addr &);
  void		handlePaquet(const PaquetJoinParty_SharedPtr &&, const Addr &);
  void		handlePaquet(const PaquetCreateParty_SharedPtr &&, const Addr &);
  void		handlePaquet(const PaquetLeave_SharedPtr &&);
  void		handlePaquet(const PaquetObstacle_SharedPtr &&);
  void		handlePaquet(const PaquetPlayerCoord_SharedPtr &&);
  void		handlePaquet(const PaquetPlayerShot_SharedPtr &&);
  void		handlePaquet(const PaquetReady_SharedPtr &&, const Addr &);
  void		handlePaquet(const PaquetRequestParties_SharedPtr &&, const Addr &);
  void		handlePaquet(const PaquetRequestPlayers_SharedPtr &&, const Addr &);
  void		handlePaquet(const PaquetResponse_SharedPtr &&);
  void		handlePaquet(const PaquetFirstUDP_SharedPtr &&, const Addr &);
  void		handlePaquet(const PaquetRename_SharedPtr &&);
  void		handlePaquet(const PaquetChat_SharedPtr &&);
};

#endif /* !MANAGER_H_ */
