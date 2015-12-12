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
#include "Manager.hh"

Party::Party(const Manager_SharedPtr &&manager)
  : _sem(std::make_unique<Semaphore>()),
    _thread(std::make_unique<Thread>()),
    _manager(std::move(manager)),
    _name("Unknwon"),
    _running(false),
    _wave(nullptr)
{
  DEBUG_MSG("Party created");
  _thread->run([this](void *) -> void * { run(); return (0); }, 0);
}

Party::Party(const Manager_SharedPtr &&manager, const std::string &name)
  : _sem(std::make_unique<Semaphore>()),
    _thread(std::make_unique<Thread>()),
    _manager(std::move(manager)),
    _name(name),
    _running(false),
    _wave(new Wave(*this))
{
  DEBUG_MSG("Party created");
  _thread->run([this](void *) -> void * { run(); return (0); }, 0);
}

Party::~Party()
{
  _players.clear();
  _enemies.clear();
  DEBUG_MSG("Party deleted");
}

void			Party::run()
{
  // PaquetEnemy	paquet;

  // paquet.setID(enemy->getID());
  // paquet.setType(enemy->getType());
  // paquet.setLife(enemy->getLife());
  // paquet.setPosition(enemy->getPosX(), enemy->getPosY());
  // paquet.createPaquet();
  // addEnemy(enemy);

  for (;;) {

    // for (auto &p : _players) {
    //   std::cout << *p << std::endl;
    //   _manager.lock()->write(paquet, p->addr());
    // }

    if (!_manager.expired()) {
//      (_manager.lock())->write(PAQUET, ADDR)
    }

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
  if (_running == false && _players.size() < 4) {
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

uint8_t			Party::getIdFromAddr(const Addr &addr) const
{
  auto &&player = Tools::findIn(_players, [&addr] (auto &p) { return (p->addr() == addr); });

  return ((player) ? (player->getID()) : (0xFF));
}

bool			Party::isPlayer(uint8_t id) const
{
  return (Tools::findIn(_players, [id] (auto &p) { return (p->getID() == id); }) != nullptr);
}

void			Party::setCoordPlayer(PlayerCoord *pc)
{
  uint8_t id = pc->getID();
  auto &&player = Tools::findIn(_players, [id] (auto &p) { return (p->getID() == id); });

  if (player) {
    std::cout << "New Position: " << (int)pc->getX() << ", " << (int)pc->getY() << std::endl;
    player->setPosition(Position(pc->getX(), pc->getY()));
  }
  delete pc;
}

void			Party::setReady(uint8_t id, uint8_t status)
{
  auto &&player = Tools::findIn(_players, [&id](auto &p) { return (p->getID() == id); });
  if (player) {
    player->setReady((status) ? (true) : (false));
  }
}

void			Party::setPlayerShot(PlayerShot *ps)
{
  // TODO: Sauvegarder les tirs, comme avec setCoordPlayer
  delete ps;
}

bool			Party::isRunning() const
{
  return (_running);
}

void			Party::setRunning(bool run)
{
  _running = run;
}


bool			Party::addEnemy(Enemy *enemy)
{
  if (enemy) {
    _enemies.emplace_back(enemy);
    return true;
  }
  return false;
}

uint8_t			Party::getUniqueID() const
{
  uint8_t		id;

  for (id = 0; id < 255; id += 1) {
    if (Tools::findIn(_players, [id] (auto &p) { return (p->getID() == id); }) == nullptr
	&& Tools::findIn(_enemies, [id] (auto &e) { return (e->getID() == id); }) == nullptr) {
      return (id);
    }
  }
  return (0xFF);
}
