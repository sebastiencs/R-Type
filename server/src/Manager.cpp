//
// Manager.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Mon Nov 23 17:49:14 2015 chapui_s
// Last update Mon Nov 23 17:49:14 2015 chapui_s
//

#include "Manager.hh"
#include "Network.hh"
#include "Tools.hh"

Manager::Manager()
 : _network()
{
  DEBUG_MSG("Manager created");
}

Manager::~Manager()
{
  DEBUG_MSG("Manager deleted");
}

const Manager_SharedPtr	Manager::getPtr()
{
  return (shared_from_this());
}

void		Manager::write(const Paquet &paquet, const Addr &addr) const
{
  if (!_network.expired()) {
    (_network.lock())->write(paquet, addr);
  }
  else {
    DEBUG_MSG("Try to send on null network");
  }
}

void		Manager::broadcast(const PlayerList &list, const Paquet &paquet) const
{
  if (!_network.expired()) {

    auto net = _network.lock();

    list.for_each([&] (auto &p) {
	net->write(paquet, p->addr());
      });

  }
  else {
    DEBUG_MSG("Try to send on null network");
  }
}

void		Manager::broadcast_nolock(const PlayerList &list, const Paquet &paquet) const
{
  if (!_network.expired()) {

    auto net = _network.lock();

    for (auto &elem : list) {
      net->write(paquet, elem->addr());
    }

  }
  else {
    DEBUG_MSG("Try to send on null network");
  }
}

void		Manager::broadcast_except(const PlayerList &list, const uint8_t id, const Paquet &paquet) const
{
  if (!_network.expired()) {

    auto net = _network.lock();

    list.for_each([&, id] (auto &p) {
	if (p->getID() != id) {
	  net->write(paquet, p->addr());
	}
      });

  }
  else {
    DEBUG_MSG("Try to send on null network");
  }
}

void		Manager::deletePlayer(const Addr &addr)
{
  {
    auto &&player = _pWaiting.findIn([&addr] (auto &p) { return (p->addr() == addr); });

    if (player != nullptr) {
      _pWaiting.remove(player);
      return ;
    }
  }
  {
    auto &&party = _parties.findIn([&addr] (auto &p) { return (p->isPlayer(addr)); });
    uint8_t id = 0xFF;

    if (!party) {
      return ;
    }

    id = party->getIdFromAddr(addr);
    party->deletePlayer(addr);

    if (party->getPlayers().empty()) {
      _parties.remove(party);
    }
    else {

      auto &players = party->getPlayers();

      std::shared_ptr<Paquet> paquet;

      if (party->isRunning()) {
	paquet = std::make_shared<PaquetLeave>(id);
      }
      else {
	paquet = std::make_shared<PaquetListPlayers>(players);
      }

      broadcast(players, *paquet);
    }
  }
}

void		Manager::setNetwork(const INetwork_SharedPtr &&network)
{
  _network = std::move(network);
}

uint8_t		Manager::getID() const
{
  static uint8_t	id = 0;

  // TODO: check if id isn't use by another player
  if (id == 0xFF) {
    id = 0;
  }
  return (id++);
}

void		Manager::handlePaquet(const PaquetFirst_SharedPtr &&paquet, const Addr &addr)
{
  PaquetResponse	p;

  DEBUG_MSG(*paquet);

  if (paquet->getVersion() == 1) {
    uint8_t id = getID();
    _pWaiting.emplace_back(std::make_shared<Player>(paquet->getName(), id, paquet->getLevel(), addr, 80, 91));
    p.setReturn(2);
    p.setData(id);
  }
  else {
    p.setReturn(0);
  }
  p.createPaquet();
  write(p, addr);
}

void		Manager::handlePaquet(const PaquetJoinParty_SharedPtr &&paquet, const Addr &addr)
{
  const std::string	&name = paquet->getName();

  DEBUG_MSG(*paquet);

  auto &&party = _parties.findIn([&name] (auto &p) { return (p->getName() == name); });
  auto &&player = _pWaiting.findIn([&addr] (auto &p) { return (p->addr() == addr); });

  PaquetResponse	p;

  if (party && player && party->addPlayer(player)) {
    _pWaiting.remove(player);
    p.setReturn(4);
    p.createPaquet();
    write(p, addr);

    auto &players = party->getPlayers();
    PaquetListPlayers	paquet(players);

    broadcast(players, paquet);
  }
  else {
    p.setReturn(3);
    p.createPaquet();
    write(p, addr);
#ifdef DEBUG
    if (!player) {
      std::cerr << "JoinParty: Can't find player" << std::endl;
    }
    if (!party) {
      std::cerr << "JoinParty: Can't find party" << std::endl;
    }
    if (party && player) {
      std::cerr << "JoinParty: Too many players or party already running" << std::endl;
    }
#endif // !DEBUG
  }
}

void		Manager::handlePaquet(const PaquetCreateParty_SharedPtr &&paquet, const Addr &addr)
{
  const std::string	&name = paquet->getName();

  DEBUG_MSG(*paquet);

  auto &&party = _parties.findIn([&name] (auto &p) { return (p->getName() == name); });
  auto &&player = _pWaiting.findIn([&addr] (auto &p) { return (p->addr() == addr); });

  PaquetResponse	p;

  if (!party && player && name.size()) {
    auto party = std::make_shared<Party>(shared_from_this(), name);

    party->addPlayer(player);
    _pWaiting.remove(player);
    _parties.push_back(party);
    p.setReturn(4);
  }
  else {
    p.setReturn(3);
#ifdef DEBUG
    if (party) {
      std::cerr << "CreateParty: Party already exist" << std::endl;
    }
    if (!player) {
      std::cerr << "CreateParty: Can't find player. Already in Game ?" << std::endl;
    }
#endif // !DEBUG
  }
  p.createPaquet();
  write(p, addr);
}

void		Manager::handlePaquet(const PaquetLeave_SharedPtr &&paquet)
{
  uint8_t	id = paquet->getID();

  DEBUG_MSG(*paquet);

  auto &&party = _parties.findIn([id] (auto &p) { return (p->isPlayer(id)); });

  if (party) {
    const Player_SharedPtr &&p = party->playerLeave(id);
    if (p) {
      _pWaiting.emplace_back(p);
    }

    auto &players = party->getPlayers();

    if (players.empty()) {
      _parties.remove(party);
    }
    else {
      auto &players = party->getPlayers();
      PaquetListPlayers	paquet(players);

      broadcast(players, paquet);
    }
  }
  else {
    std::cout << "Can't find party PaquetLeave)" << std::endl;
  }
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(const PaquetObstacle_SharedPtr &&paquet UNUSED)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(const PaquetPlayerCoord_SharedPtr &&paquet)
{
  uint8_t	id = paquet->getPlayerID();

  DEBUG_MSG(*paquet);

  auto &&party = _parties.findIn([id] (auto &p) { return (p->isPlayer(id)); });
  if (party) {

    party->setCoordPlayer(paquet->getPlayerID(), paquet->getX(), paquet->getY());

    auto &&players = party->getPlayers();
    auto &&player = players.findIn([id] (auto &p) { return (p->getID() == id); });

    if (player) {
      PaquetPlayerCoord paquet(player);
      broadcast_except(players, id, paquet);
    }
  }
#ifdef DEBUG
  else {
    if (!party) {
      std::cerr << "Can't find party" << std::endl;
    }
  }
#endif // !DEBUG
}

void		Manager::handlePaquet(const PaquetPlayerShot_SharedPtr &&paquet)
{
  uint8_t	id = paquet->getPlayerID();

  DEBUG_MSG(*paquet);

  auto &&party = _parties.findIn([id](auto &p) { return (p->isPlayer(id)); });
  if (party) {
    party->setPlayerShot(paquet->getPlayerID(), paquet->getX(), paquet->getY(), paquet->getSpeed(), paquet->getType());

    auto &&players = party->getPlayers();
    broadcast_except(players, id, *paquet);
  }
#ifdef DEBUG
  else {
    if (!party) {
      std::cerr << "Can't find party" << std::endl;
    }
  }
#endif // !DEBUG
}

void		Manager::handlePaquet(const PaquetReady_SharedPtr &&paquet, const Addr &addr)
{
  DEBUG_MSG(*paquet);

  size_t	size = 0;
  PaquetLaunch	p;

  uint8_t	id = paquet->getID();
  auto &&party = _parties.findIn([&addr](auto &p) { return (p->isPlayer(addr)); });

  if (party) {

    party->setReady(id, paquet->getStatus());
    auto &players = party->getPlayers();

    broadcast_except(players, id, *paquet);
    size = players.count_if([] (auto &p) { return (p->getReady()); });

    if (players.size() == size) {
      party->setRunning(true);
      broadcast(players, p);
    }
  }
  else {
#ifdef DEBUG
    if (!party) {
      std::cerr << "Ready: Can't find party" << std::endl;
    }
#endif // !DEBUG
  }
}

void		Manager::handlePaquet(const PaquetRequestParties_SharedPtr &&paquet UNUSED, const Addr &addr)
{
  PaquetListParties	p;

  DEBUG_MSG(*paquet);

  for (auto &party : _parties) {
    if (party->isRunning() == false) {
      p.addParty(party->getName(), party->getNb());
    }
  }
  p.createPaquet();
  write(p, addr);
}

void		Manager::handlePaquet(const PaquetRequestPlayers_SharedPtr &&paquet UNUSED, const Addr &addr)
{
  PaquetListPlayers	p;

  DEBUG_MSG(*paquet);

  auto &&party = _parties.findIn([&addr] (auto &p) { return (p->isPlayer(addr)); });

  if (party) {
    p = party->getPlayers();
  }
  write(p, addr);
}

void		Manager::handlePaquet(const PaquetResponse_SharedPtr &&paquet UNUSED)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(const PaquetFirstUDP_SharedPtr &&paquet, const Addr &addr)
{
  DEBUG_MSG(*paquet);

  uint8_t	id = paquet->getId();

  auto &&p = _pWaiting.findIn([id] (auto &p) { return (p->getID() == id); });

  if (p) {
    p->addr().setPortUDP(addr.get().sin_port);
  }
}

void		Manager::handlePaquet(const PaquetRename_SharedPtr &&paquet)
{
  uint8_t	id = paquet->getID();

  DEBUG_MSG(*paquet);

  if (paquet->getName().empty()) {
    DEBUG_MSG("Trying to rename a player with an empty name");
    return ;
  }

  auto &&party = _parties.findIn([id] (auto &p) { return (p->isPlayer(id)); });
  if (party) {

    party->renamePlayer(id, paquet->getName());

    auto &&players = party->getPlayers();
    broadcast_except(players, id, *paquet);
  }
  else {

    auto &&player = _pWaiting.findIn([id] (auto &p) { return (p->getID() == id); });

    if (player) {
      player->setName(paquet->getName());
    }
  }
}

void		Manager::handlePaquet(const PaquetChat_SharedPtr &&paquet)
// void		Manager::handlePaquet(PaquetChat_SharedPtr paquet, const Addr &addr UNUSED)
{
  uint8_t	id = paquet->getID();

  DEBUG_MSG(*paquet);

  auto &&party = _parties.findIn([id] (auto &p) { return (p->isPlayer(id)); });
  if (party) {
    auto &&players = party->getPlayers();
    broadcast_except(players, id, *paquet);
  }
}
