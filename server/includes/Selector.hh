//
// Selector.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Mon Nov 16 14:50:07 2015 chapui_s
// Last update Mon Nov 16 14:50:07 2015 chapui_s
//

#ifndef SELECTOR_H_
# define SELECTOR_H_

# include <map>
# include <functional>
# include "Paquets.hh"

class		Manager;

typedef std::map<uint8_t, std::function<void (const Buffer &)>>	listFunc;

class		Selector
{
private:
  Manager	*_manager;

  listFunc	_selectorFunc;

public:

  template<class Arg>
  auto resolver(void (Manager::*func)(Arg) = &Manager::handlePaquet) -> decltype(func)
    { return func; }

  // template<class Arg>
  // auto resolver(void (Manager::*func)(Arg)) -> decltype(func) { return func; }

  Selector(Manager *manager) {
   _manager = manager;

   _selectorFunc[Paquet::FIRST] = [this](const Buffer &buf) {
     (_manager->*resolver<PaquetFirst *>())(new PaquetFirst(buf));
   };
   _selectorFunc[Paquet::CREATE_PARTY] = [this](const Buffer &buf) {
     (_manager->*resolver<PaquetCreateParty *>())(new PaquetCreateParty(buf));
   };
   _selectorFunc[Paquet::JOIN_PARTY] = [this](const Buffer &buf) {
     (_manager->*resolver<PaquetJoinParty *>())(new PaquetJoinParty(buf));
   };
   _selectorFunc[Paquet::LAUNCH] = [this](const Buffer &buf) {
     (_manager->*resolver<PaquetLaunch *>())(new PaquetLaunch(buf));
   };
   _selectorFunc[Paquet::LEAVE] = [this](const Buffer &buf) {
     (_manager->*resolver<PaquetLeave *>())(new PaquetLeave(buf));
   };
   _selectorFunc[Paquet::LIST_PARTIES] = [this](const Buffer &buf) {
     (_manager->*resolver<PaquetListParties *>())(new PaquetListParties(buf));
   };
   _selectorFunc[Paquet::LIST_PLAYERS] = [this](const Buffer &buf) {
     (_manager->*resolver<PaquetListPlayers *>())(new PaquetListPlayers(buf));
   };
   _selectorFunc[Paquet::OBSTACLE] = [this](const Buffer &buf) {
     (_manager->*resolver<PaquetObstacle *>())(new PaquetObstacle(buf));
   };
   _selectorFunc[Paquet::COORD_PLAYER] = [this](const Buffer &buf) {
     (_manager->*resolver<PaquetPlayerCoord *>())(new PaquetPlayerCoord(buf));
   };
   _selectorFunc[Paquet::PLAYER_SHOT] = [this](const Buffer &buf) {
     (_manager->*resolver<PaquetPlayerShot *>())(new PaquetPlayerShot(buf));
   };
   _selectorFunc[Paquet::READY] = [this](const Buffer &buf) {
     (_manager->*resolver<PaquetReady *>())(new PaquetReady(buf));
   };
   _selectorFunc[Paquet::REQUEST_PARTIES] = [this](const Buffer &buf) {
     (_manager->*resolver<PaquetRequestParties *>())(new PaquetRequestParties(buf));
   };
   _selectorFunc[Paquet::REQUEST_PLAYERS] = [this](const Buffer &buf) {
     (_manager->*resolver<PaquetRequestPlayers *>())(new PaquetRequestPlayers(buf));
   };
   _selectorFunc[Paquet::RESPONSE] = [this](const Buffer &buf) {
     (_manager->*resolver<PaquetResponse *>())(new PaquetResponse(buf));
   };


   // _selectorFunc[Paquet::FIRST] = [this](const Buffer &buf) {
   //   (_manager->*resolver<PaquetFirst *>(&Manager::handlePaquet))(new PaquetFirst(buf));
   // };
   // _selectorFunc[Paquet::CREATE_PARTY] = [this](const Buffer &buf) {
   //   (_manager->*resolver<PaquetCreateParty *>(&Manager::handlePaquet))(new PaquetCreateParty(buf));
   // };
   // _selectorFunc[Paquet::JOIN_PARTY] = [this](const Buffer &buf) {
   //   (_manager->*resolver<PaquetJoinParty *>(&Manager::handlePaquet))(new PaquetJoinParty(buf));
   // };
   // _selectorFunc[Paquet::LAUNCH] = [this](const Buffer &buf) {
   //   (_manager->*resolver<PaquetLaunch *>(&Manager::handlePaquet))(new PaquetLaunch(buf));
   // };
   // _selectorFunc[Paquet::LEAVE] = [this](const Buffer &buf) {
   //   (_manager->*resolver<PaquetLeave *>(&Manager::handlePaquet))(new PaquetLeave(buf));
   // };
   // _selectorFunc[Paquet::LIST_PARTIES] = [this](const Buffer &buf) {
   //   (_manager->*resolver<PaquetListParties *>(&Manager::handlePaquet))(new PaquetListParties(buf));
   // };
   // _selectorFunc[Paquet::LIST_PLAYERS] = [this](const Buffer &buf) {
   //   (_manager->*resolver<PaquetListPlayers *>(&Manager::handlePaquet))(new PaquetListPlayers(buf));
   // };
   // _selectorFunc[Paquet::OBSTACLE] = [this](const Buffer &buf) {
   //   (_manager->*resolver<PaquetObstacle *>(&Manager::handlePaquet))(new PaquetObstacle(buf));
   // };
   // _selectorFunc[Paquet::COORD_PLAYER] = [this](const Buffer &buf) {
   //   (_manager->*resolver<PaquetPlayerCoord *>(&Manager::handlePaquet))(new PaquetPlayerCoord(buf));
   // };
   // _selectorFunc[Paquet::PLAYER_SHOT] = [this](const Buffer &buf) {
   //   (_manager->*resolver<PaquetPlayerShot *>(&Manager::handlePaquet))(new PaquetPlayerShot(buf));
   // };
   // _selectorFunc[Paquet::READY] = [this](const Buffer &buf) {
   //   (_manager->*resolver<PaquetReady *>(&Manager::handlePaquet))(new PaquetReady(buf));
   // };
   // _selectorFunc[Paquet::REQUEST_PARTIES] = [this](const Buffer &buf) {
   //   (_manager->*resolver<PaquetRequestParties *>(&Manager::handlePaquet))(new PaquetRequestParties(buf));
   // };
   // _selectorFunc[Paquet::REQUEST_PLAYERS] = [this](const Buffer &buf) {
   //   (_manager->*resolver<PaquetRequestPlayers *>(&Manager::handlePaquet))(new PaquetRequestPlayers(buf));
   // };
   // _selectorFunc[Paquet::RESPONSE] = [this](const Buffer &buf) {
   //   (_manager->*resolver<PaquetResponse *>(&Manager::handlePaquet))(new PaquetResponse(buf));
   // };
  }

  virtual ~Selector() {};

  int		execFunc(const Buffer &);
};

int		Selector::execFunc(const Buffer &buf)
{
  Data		*data = buf.get();

  if (!data || buf.size() <= 0) {
    std::cerr << "Wrong paquet size" << std::endl;
    return (-1);
  }

  auto func = _selectorFunc.find(data[0]);

  if (func != _selectorFunc.end()) {
    func->second(buf);
    return (0);
  }
  else {
    std::cerr << "Unknown paquet" << std::endl;
    return (-1);
  }
}

#endif /* !SELECTOR_H_ */
