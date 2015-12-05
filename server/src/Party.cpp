//
// Party.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 10 22:44:37 2015 chapui_s
// Last update Tue Nov 10 22:44:37 2015 chapui_s
//

#include "Party.hh"
#include "IOEvent.hh"
#include "Tools.hh"

Party::Party(const Manager_SharedPtr &&manager)
  : _sem(std::make_unique<Semaphore>()),
    _thread(std::make_unique<Thread>()),
    _manager(std::move(manager)),
    _name("Unknwon")
{
  DEBUG_MSG("Party created");
  _thread->run([this](void *) -> void * { run(); return (0); }, 0);
}

Party::Party(const Manager_SharedPtr &&manager, const std::string &name)
  : _sem(std::make_unique<Semaphore>()),
    _thread(std::make_unique<Thread>()),
    _manager(std::move(manager)),
    _name(name)
{
  DEBUG_MSG("Party created");
  _thread->run([this](void *) -> void * { run(); return (0); }, 0);
}

Party::~Party()
{
  _players.clear();
  DEBUG_MSG("Party deleted");
}

void			Party::run()
{
  for (;;) {
    std::cerr << "A party is running" << std::endl;

    IOEvent::wait(6000);
  }
}

void			Party::stop()
{
  _thread->close();
}

const listPlayers	&Party::getPlayers() const
{
  return (_players);
}

uint8_t			Party::getNb() const
{
  return (static_cast<uint8_t>(_players.size()));
}

const std::string	&Party::getName() const
{
  return (_name);
}

bool			Party::addPlayer(Player_SharedPtr player)
{
  if (_players.size() < 4) {
    _players.emplace_back(player);
    return (true);
  }
  else {
    return (false);
  }
}

void			Party::deletePlayer(const Addr &addr)
{
  auto p = Tools::findIn(_players, [&addr] (auto &p) { return (p->addr() == addr); });

  if (p != nullptr) {
    _players.remove(p);
    DEBUG_MSG("Player deleted from party");
  }

  if (!_players.size()) {
    DEBUG_MSG("No more players.. Party killed");
    _thread->close();
  }
}

Player_SharedPtr	Party::playerLeave(uint8_t id)
{
  auto p = Tools::findIn(_players, [id] (auto &p) { return (p->getID() == id); });

  if (p != nullptr) {
    Player_SharedPtr player = p;
    _players.remove(p);
    DEBUG_MSG("Player deleted from party");
    return (player);
  }
  return (nullptr);
}

bool			Party::isPlayer(const Addr &addr) const
{
  return (Tools::findIn(_players, [&addr] (auto &p) { return (p->addr() == addr); }) != nullptr);
}

bool			Party::isPlayer(uint8_t id) const
{
  return (Tools::findIn(_players, [id] (auto &p) { return (p->getID() == id); }) != nullptr);
}

void			Party::setCoordPlayer(PlayerCoord *pc UNUSED)
{
}

void			Party::setReady(uint8_t id)
{
	auto &&player = Tools::findIn(_players, [&id](auto &p) { return (p->getID() == id); });
	if (player) {
		player->setReady(true);
	}
}
