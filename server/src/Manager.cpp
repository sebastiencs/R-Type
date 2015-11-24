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

void		Manager::setNetwork(Network *network)
{
  _network = network;
}

uint8_t		Manager::getID() const
{
  static uint8_t	id = 0;

  // TODO: Manage overflow
  return (id++);
}

void		Manager::handlePaquet(PaquetFirst *paquet, const Addr &addr)
{
  PaquetResponse	p;

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
  DEBUG_MSG(*paquet);
  delete paquet;
}

void		Manager::handlePaquet(PaquetJoinParty *paquet UNUSED, const Addr &addr UNUSED)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetCreateParty *paquet UNUSED, const Addr &addr UNUSED)
{
  // DEBUG_MSG(paquet);
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

void		Manager::handlePaquet(PaquetRequestParties *paquet UNUSED, const Addr &addr UNUSED)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetRequestPlayers *paquet UNUSED, const Addr &addr UNUSED)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetResponse *paquet UNUSED, const Addr &addr UNUSED)
{
  // DEBUG_MSG(paquet);
}
