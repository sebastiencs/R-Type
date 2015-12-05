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

Manager_SharedPtr	Manager::getPtr()
{
  return (shared_from_this());
}

void		Manager::write(const Paquet &paquet, const Addr &addr)
{
  if (!_network.expired()) {
    (_network.lock())->write(paquet, addr);
  }
  else {
    DEBUG_MSG("Try to send on null network");
  }
}

void		Manager::deletePlayer(const Addr &addr)
{
  {
    auto &&player = Tools::findIn(_pWaiting, [&addr] (auto &p) { return (p->addr() == addr); });

    if (player != nullptr) {
      _pWaiting.remove(player);
      return ;
    }
  }
  {
    auto &&party = Tools::findIn(_parties, [&addr] (auto &p) { return (p->isPlayer(addr)); });

    if (party != nullptr) {
      party->deletePlayer(addr);
    }
    if (party->getPlayers().empty()) {
      _parties.remove(party);
    }
  }
}

void		Manager::setNetwork(INetwork_SharedPtr &&network)
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

void		Manager::handlePaquet(PaquetFirst *paquet, const Addr &addr)
{
  PaquetResponse	p;

  DEBUG_MSG(*paquet);

  if (paquet->getVersion() == 1) {

    uint8_t id = getID();

    _pWaiting.emplace_back(std::make_shared<Player>(paquet->getName(), id, paquet->getLevel(), addr));
    p.setReturn(2);
    p.setData(id);
  }
  else {
    p.setReturn(0);
  }
  p.createPaquet();
  write(p, addr);
  delete paquet;
}

void		Manager::handlePaquet(PaquetJoinParty *paquet, const Addr &addr)
{
  const std::string	&name = paquet->getName();

  DEBUG_MSG(*paquet);

  auto &&party = Tools::findParty(_parties, name);
  auto &&player = Tools::findPlayer(_pWaiting, addr);

  PaquetResponse	p;

  if (party && player && party->addPlayer(player)) {
    _pWaiting.remove(player);
    p.setReturn(4);
    p.createPaquet();
    write(p, addr);

    auto &players = party->getPlayers();
    PaquetListPlayers	paquet;
    for (auto &p : players) {
      paquet.addPlayer(p->getName(), p->getID(), p->getLevel());
    }
    paquet.createPaquet();
    for (auto &p : players) {
      write(paquet, p->addr());
    }
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
      std::cerr << "JoinParty: Too many players" << std::endl;
    }
#endif // !DEBUG
  }
  delete paquet;
}

void		Manager::handlePaquet(PaquetCreateParty *paquet, const Addr &addr)
{
  const std::string	&name = paquet->getName();

  DEBUG_MSG(*paquet);

  auto &&party = Tools::findParty(_parties, name);
  auto &&player = Tools::findPlayer(_pWaiting, addr);

  PaquetResponse	p;

  if (!party && player) {
    Party	*party(new Party(shared_from_this(), name));

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
  delete paquet;
}

void		Manager::handlePaquet(PaquetLeave *paquet, const Addr &addr UNUSED)
{
  uint8_t	id = paquet->getID();

  DEBUG_MSG(*paquet);

  auto &&party = Tools::findIn(_parties, [id] (Party *p) { return (p->isPlayer(id)); });

  if (party) {
    Player_SharedPtr &&p = party->playerLeave(id);
    if (p) {
      _pWaiting.emplace_back(p);
    }

    auto &players = party->getPlayers();

    if (players.empty()) {
      _parties.remove(party);
    }
    else {
      for (auto &player : players) {
	write(*paquet, player->addr());
      }
    }
  }
  else {
    std::cout << "Can't find party (PaquetLeave)" << std::endl;
  }
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetListParties *paquet UNUSED, const Addr &addr UNUSED)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetListPlayers *paquet UNUSED, const Addr &addr UNUSED)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetObstacle *paquet UNUSED, const Addr &addr UNUSED)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetPlayerCoord *paquet, const Addr &addr UNUSED)
{
  uint8_t	id = paquet->getPlayerID();

  DEBUG_MSG(*paquet);

  auto &&party = Tools::findIn(_parties, [id] (Party *p) { return (p->isPlayer(id)); });
  auto pc = new PlayerCoord(paquet->getX(), paquet->getY(), paquet->getPlayerID());
  if (party && pc) {
    party->setCoordPlayer(pc);
  }
  else {
#ifdef DEBUG
    if (!party) {
      std::cerr << "Can't find party" << std::endl;
    }
#endif // !DEBUG
  }
  delete paquet;
}

void		Manager::handlePaquet(PaquetPlayerShot *paquet UNUSED, const Addr &addr UNUSED)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetReady *paquet, const Addr &addr)
{
	DEBUG_MSG(*paquet);

	size_t			size = 0;
	PaquetLaunch	p;

	uint8_t	id = paquet->getID();
	auto &&party = Tools::findIn(_parties, [&addr](Party *p) { return (p->isPlayer(addr)); });

	if (party) {

		party->setReady(id);
		auto &players = party->getPlayers();

		for (auto &player : players) {
			write(*paquet, player->addr());
			if (player->getReady()) {
				size++;
			}
		}

		if (players.size() == size) {
			p.createPaquet();
			for (auto &player : players) {
				write(p, player->addr());
			}
		}
	}
#ifdef DEBUG
	if (!party) {
		std::cerr << "Ready: Can't find party" << std::endl;
	}
#endif // !DEBUG
	delete paquet;
}


void		Manager::handlePaquet(PaquetRequestParties *paquet, const Addr &addr)
{
  PaquetListParties	p;

  DEBUG_MSG(*paquet);

  for (auto &party : _parties) {
    p.addParty(party->getName(), party->getNb());
  }
  p.createPaquet();
  write(p, addr);
  delete paquet;
}

void		Manager::handlePaquet(PaquetRequestPlayers *paquet, const Addr &addr)
{
  PaquetListPlayers	p;

  DEBUG_MSG(*paquet);

  auto &&party = Tools::findIn(_parties, [&addr] (Party *p) { return (p->isPlayer(addr)); });

  if (party) {

    const listPlayers &plist = party->getPlayers();

    for (auto &player : plist) {
      p.addPlayer(player->getName(), player->getID(), player->getLevel());
    }
  }
  p.createPaquet();
  write(p, addr);
  delete paquet;
}

void		Manager::handlePaquet(PaquetResponse *paquet UNUSED, const Addr &addr UNUSED)
{
  // DEBUG_MSG(paquet);
}
