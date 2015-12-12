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
    _wave(std::make_unique<Wave>(*this)),
    _timerWave(std::make_unique<Timer>())
{
  DEBUG_MSG("Party created");
}

Party::Party(const Manager_SharedPtr &&manager, const std::string &name)
  : _sem(std::make_unique<Semaphore>()),
    _thread(std::make_unique<Thread>()),
    _manager(std::move(manager)),
    _name(name),
    _running(false),
    _wave(std::make_unique<Wave>(*this)),
    _timerWave(std::make_unique<Timer>())
{
  DEBUG_MSG("Party created");
}

Party::~Party()
{
  _players.clear();
  _enemies.clear();
  DEBUG_MSG("Party deleted");
}

void			Party::write(const Paquet &paquet, const Addr &addr) const
{
  if (!_manager.expired()) {
    _manager.lock()->write(paquet, addr);
  }
}

void			Party::updateEnemy(const Enemy_SharedPtr &e)
{
  PaquetEnemy		paquet;

  paquet = e;
  _players.for_each([&] (auto &p) {
      write(paquet, p->addr());
    });
}

void			Party::run()
{
  PaquetEnemy	paquet;

  _timerWave->start();

  for (;;) {

    if (_enemies.empty() || _timerWave->ms() >= 100000) {
      _wave->getSpawn();
      _enemies.for_each([this] (auto &enemy) {
	  updateEnemy(enemy);
	});
      _timerWave->reset();
    }

    _enemies.for_each([&] (auto &enemy) {
	uint16_t y = enemy->getPosY();
	auto focused = focusOnClosestPlayer(y);
	bool changed = false;

	if (focused && focused->getPosition().y < y - 3) {
	  enemy->setPosY(y - 2);
	  changed = true;
	}
	else if (focused && focused->getPosition().y > y + 3) {
	  enemy->setPosY(y + 2);
	  changed = true;
	}
	if (changed) {
	  updateEnemy(enemy);
	}
      });

    IOEvent::wait(20);
  }
}

const Player_SharedPtr	Party::focusOnClosestPlayer(const uint8_t yEnemy) const
{
  uint8_t idClosest = 0xFF;
  uint16_t distance = 0xFFFF;

  _players.for_each([&] (auto &p) mutable {
      uint16_t tmp = std::abs(p->getPosition().y - yEnemy);
      if (tmp < distance) {
	idClosest = p->getID();
	distance = tmp;
      }
    });

  return (_players.findIn([idClosest] (auto &p) { return (p->getID() == idClosest); }));
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
  auto &&p = _players.findIn([&addr] (auto &p) { return (p->addr() == addr); });

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
  auto &&p = _players.findIn([id] (auto &p) { return (p->getID() == id); });

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
  return (_players.findIn([&addr] (auto &p) { return (p->addr() == addr); }) != nullptr);
}

uint8_t			Party::getIdFromAddr(const Addr &addr) const
{
  auto &&player = _players.findIn([&addr] (auto &p) { return (p->addr() == addr); });

  return ((player) ? (player->getID()) : (0xFF));
}

bool			Party::isPlayer(uint8_t id) const
{
  return (_players.findIn([id] (auto &p) { return (p->getID() == id); }) != nullptr);
}

void			Party::setCoordPlayer(PlayerCoord *pc)
{
  uint8_t id = pc->getID();
  auto &&player = _players.findIn([id] (auto &p) { return (p->getID() == id); });

  if (player) {
    player->setPosition(Position(pc->getX(), pc->getY()));
  }
  delete pc;
}

void			Party::setReady(uint8_t id, uint8_t status)
{
  auto &&player = _players.findIn([&id](auto &p) { return (p->getID() == id); });
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
  if (run == true) {
    _thread->run([this](void *) -> void * { this->run(); return (0); }, 0);
    Position pos;
    PaquetPlayerCoord	paquet;
    int i = 1;

    _players.for_each([&] (auto &player) {
	pos = player->getPosition();
	pos.y += 200 * i;
	player->setPosition(pos);

	paquet.setPlayerID(player->getID());
	paquet.setPosition(pos.x, pos.y);
	paquet.createPaquet();
	write(paquet, player->addr());
      });
  }
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
    if (_players.findIn([id] (auto &p) { return (p->getID() == id); }) == nullptr
	&& _enemies.findIn([id] (auto &e) { return (e->getID() == id); }) == nullptr) {
      return (id);
    }
  }
  return (0xFF);
}
