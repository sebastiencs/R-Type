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

Manager::Manager()
  : _network(0)
{
  DEBUG_MSG("Manager created");
}

Manager::~Manager()
{
  DEBUG_MSG("Manager deleted");
}

void		Manager::write(const Paquet &paquet, const Addr &addr)
{
  if (_network) {
    _network->write(paquet, addr);
  }
  else {
    DEBUG_MSG("Try to send on null network");
  }
}

void		Manager::deletePlayer(socket_t socket)
{
  for (PlayerList::iterator it = _pWaiting.begin(); it != _pWaiting.end(); ++it) {
    if ((*it)->socket() == socket) {
      delete *it;
      _pWaiting.erase(it);
      return ;
    }
  }
  for (auto &party : _parties) {
    party->deletePlayer(socket);
  }
}

void		Manager::setNetwork(Network *network)
{
  _network = network;
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

    _pWaiting.push_back(new Player(paquet->getName(), id, paquet->getLevel(), addr));
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
  std::string	name = paquet->getName();
  Party		*party = 0;
  Player	*player;

  DEBUG_MSG(*paquet);

  auto pa = std::find_if(_parties.begin(), _parties.end(), [&name](Party *p) { return (p->getName() == name); });
  party = (pa != _parties.end()) ? (*pa) : (0);

  auto pl = std::find_if(_pWaiting.begin(), _pWaiting.end(), [&addr] (Player *p) { return (p->socket() == addr.getSocket()); });
  player = (pl != _pWaiting.end()) ? (*pl) : (0);

  PaquetResponse	p;

  if (party && player && party->addPlayer(player)) {
    _pWaiting.remove(player);
    p.setReturn(4);

  }
  else {
    p.setReturn(3);
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
  p.createPaquet();
  write(p, addr);
  delete paquet;
}

void		Manager::handlePaquet(PaquetCreateParty *paquet, const Addr &addr)
{
  std::string	name = paquet->getName();
  Player	*player;

  auto pa = std::find_if(_parties.begin(), _parties.end(), [&name](Party *p) { return (p->getName() == name); });

  auto pl = std::find_if(_pWaiting.begin(), _pWaiting.end(), [&addr] (Player *p) { return (p->socket() == addr.getSocket()); });
  player = (pl != _pWaiting.end()) ? (*pl) : (0);

  PaquetResponse	p;

  if (pa != _parties.end() && player) {
    Party	*party(new Party(name));
    party->addPlayer(player);
    _pWaiting.remove(player);
    _parties.push_back(party);
    p.setReturn(4);
  }
  else {
    p.setReturn(3);
#ifdef DEBUG
    if (pa == _parties.end()) {
      std::cerr << "CreateParty: Party already exist" << std::endl;
    }
    if (!player) {
      std::cerr << "JoinParty: Can't find player" << std::endl;
    }
#endif // !DEBUG
  }
  p.createPaquet();
  write(p, addr);
  delete paquet;
}

void		Manager::handlePaquet(PaquetLaunch *paquet UNUSED, const Addr &addr UNUSED)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetLeave *paquet UNUSED, const Addr &addr UNUSED)
{
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

void		Manager::handlePaquet(PaquetPlayerCoord *paquet UNUSED, const Addr &addr UNUSED)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetPlayerShot *paquet UNUSED, const Addr &addr UNUSED)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetReady *paquet UNUSED, const Addr &addr UNUSED)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetRequestParties *paquet, const Addr &addr)
{
  PaquetListParties	p;

  for (auto &party : _parties) {
    p.addParty(party->getName(), party->getNb());
  }
  p.createPaquet();
  write(p, addr);
  DEBUG_MSG(*paquet);
  delete paquet;
}

void		Manager::handlePaquet(PaquetRequestPlayers *paquet UNUSED, const Addr &addr UNUSED)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetResponse *paquet UNUSED, const Addr &addr UNUSED)
{
  // DEBUG_MSG(paquet);
}
