//
// Selector.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 24 04:25:50 2015 chapui_s
// Last update Tue Nov 24 04:25:50 2015 chapui_s
//

#include "Selector.hh"
#include "Manager.hh"

Selector::Selector(Manager *manager) {
  _manager = manager;

  _selectorFunc[Paquet::FIRST] = [this](const Buffer &buf, const Addr &addr) {
    (_manager->*resolver<PaquetFirst *>(&Manager::handlePaquet))(new PaquetFirst(buf), addr);
  };
  _selectorFunc[Paquet::CREATE_PARTY] = [this](const Buffer &buf, const Addr &addr) {
    (_manager->*resolver<PaquetCreateParty *>(&Manager::handlePaquet))(new PaquetCreateParty(buf), addr);
  };
  _selectorFunc[Paquet::JOIN_PARTY] = [this](const Buffer &buf, const Addr &addr) {
    (_manager->*resolver<PaquetJoinParty *>(&Manager::handlePaquet))(new PaquetJoinParty(buf), addr);
  };
  _selectorFunc[Paquet::LAUNCH] = [this](const Buffer &buf, const Addr &addr) {
    (_manager->*resolver<PaquetLaunch *>(&Manager::handlePaquet))(new PaquetLaunch(buf), addr);
  };
  _selectorFunc[Paquet::LEAVE] = [this](const Buffer &buf, const Addr &addr) {
    (_manager->*resolver<PaquetLeave *>(&Manager::handlePaquet))(new PaquetLeave(buf), addr);
  };
  _selectorFunc[Paquet::LIST_PARTIES] = [this](const Buffer &buf, const Addr &addr) {
    (_manager->*resolver<PaquetListParties *>(&Manager::handlePaquet))(new PaquetListParties(buf), addr);
  };
  _selectorFunc[Paquet::LIST_PLAYERS] = [this](const Buffer &buf, const Addr &addr) {
    (_manager->*resolver<PaquetListPlayers *>(&Manager::handlePaquet))(new PaquetListPlayers(buf), addr);
  };
  _selectorFunc[Paquet::OBSTACLE] = [this](const Buffer &buf, const Addr &addr) {
    (_manager->*resolver<PaquetObstacle *>(&Manager::handlePaquet))(new PaquetObstacle(buf), addr);
  };
  _selectorFunc[Paquet::COORD_PLAYER] = [this](const Buffer &buf, const Addr &addr) {
    (_manager->*resolver<PaquetPlayerCoord *>(&Manager::handlePaquet))(new PaquetPlayerCoord(buf), addr);
  };
  _selectorFunc[Paquet::PLAYER_SHOT] = [this](const Buffer &buf, const Addr &addr) {
    (_manager->*resolver<PaquetPlayerShot *>(&Manager::handlePaquet))(new PaquetPlayerShot(buf), addr);
  };
  _selectorFunc[Paquet::READY] = [this](const Buffer &buf, const Addr &addr) {
    (_manager->*resolver<PaquetReady *>(&Manager::handlePaquet))(new PaquetReady(buf), addr);
  };
  _selectorFunc[Paquet::REQUEST_PARTIES] = [this](const Buffer &buf, const Addr &addr) {
    (_manager->*resolver<PaquetRequestParties *>(&Manager::handlePaquet))(new PaquetRequestParties(buf), addr);
  };
  _selectorFunc[Paquet::REQUEST_PLAYERS] = [this](const Buffer &buf, const Addr &addr) {
    (_manager->*resolver<PaquetRequestPlayers *>(&Manager::handlePaquet))(new PaquetRequestPlayers(buf), addr);
  };
  _selectorFunc[Paquet::RESPONSE] = [this](const Buffer &buf, const Addr &addr) {
    (_manager->*resolver<PaquetResponse *>(&Manager::handlePaquet))(new PaquetResponse(buf), addr);
  };
}

Selector::~Selector()
{
}

int		Selector::execFunc(const Buffer &buf, const Addr &addr)
{
  Data		*data = buf.get();

  if (!data || buf.size() <= 0) {
    std::cerr << "Wrong paquet size" << std::endl;
    return (-1);
  }

  auto func = _selectorFunc.find(data[0]);

  if (func != _selectorFunc.end()) {
    func->second(buf, addr);
    return (0);
  }
  else {
    std::cerr << "Unknown paquet" << std::endl;
    return (-1);
  }
}
