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

Manager::Manager()
{
  DEBUG_MSG("Manager created");
}

Manager::~Manager()
{
  DEBUG_MSG("Manager deleted");
}

void		Manager::handlePaquet(PaquetFirst *paquet)
{
  DEBUG_MSG(*paquet);
}

void		Manager::handlePaquet(PaquetJoinParty *paquet)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetCreateParty *paquet)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetLaunch *paquet)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetLeave *paquet)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetListParties *paquet)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetListPlayers *paquet)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetObstacle *paquet)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetPlayerCoord *paquet)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetPlayerShot *paquet)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetReady *paquet)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetRequestParties *paquet)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetRequestPlayers *paquet)
{
  // DEBUG_MSG(paquet);
}

void		Manager::handlePaquet(PaquetResponse *paquet)
{
  // DEBUG_MSG(paquet);
}
