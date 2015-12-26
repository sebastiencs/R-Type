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
#include "Physics.hh"

Party::Party(const Manager_SharedPtr &&manager)
  : _sem(std::make_unique<Semaphore>()),
    _thread(std::make_unique<Thread>()),
    _manager(std::move(manager)),
    _name("Unknwon"),
    _running(false),
    _wave(std::make_unique<Wave>(*this)),
    _timerBonus(std::make_unique<Timer>()),
    _timerBullet(std::make_unique<Timer>())
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
    _timerBonus(std::make_unique<Timer>()),
    _timerBullet(std::make_unique<Timer>())
{
  DEBUG_MSG("Party created");
}

Party::~Party()
{
  _players.clear();
  _enemies.clear();
  _bonusmalus.clear();
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
      this->write(paquet, p->addr());
    });
}

void			Party::updateBonus(const BonusMalus_SharedPtr &e)
{
  PaquetBonusMalus	paquet;

  paquet = e;
  _players.for_each([&] (auto &p) {
      this->write(paquet, p->addr());
    });
}

void			Party::broadcast(const listPlayers &list, const Paquet &paquet)
{
  if (!_manager.expired()) {
    _manager.lock()->broadcast(list, paquet);
  }
}

void			Party::broadcast_nolock(const listPlayers &list, const Paquet &paquet)
{
  if (!_manager.expired()) {
    _manager.lock()->broadcast_nolock(list, paquet);
  }
}

void			Party::run()
{
  PaquetEnemy	paquet;

  _timerBonus->start();
  _timerBullet->start();

  for (;;) {

    if (_timerBonus->ms() >= 10000) {
      _wave->getSpawnBonusMalus();
      _bonusmalus.for_each([this] (auto &b) {
	  this->updateBonus(b);
	});
      _timerBonus->reset();
    }

    if (_enemies.empty()) {
      _wave->getSpawnEnemy();
      _enemies.for_each([this] (auto &enemy) {
    	  this->updateEnemy(enemy);
    	});
    }

    _enemies.for_each([&] (auto &enemy) {

	bool changed = false;

	if (enemy->getStatus() == Enemy::JUST_ENTERED) {

	  uint16_t x = enemy->getX();
	  if (x > enemy->getColumn()) {
	    changed = Physics::moveX(Physics::NO_LOCK, enemy, x - 2, _enemies, _players);
	  }
	  else {
	    enemy->nextAction();
	  }
	}
	else if (enemy->getStatus() == Enemy::FOLLOWING) {

	  uint16_t y = enemy->getY();
	  auto focused = this->focusOnClosestPlayer(y);

	  if (focused && focused->getPosition().y < y - 3) {
	    changed = Physics::moveY(Physics::NO_LOCK, enemy, y - 2, _enemies, _players);
	  }
	  else if (focused && focused->getPosition().y > y + 3) {
	    changed = Physics::moveY(Physics::NO_LOCK, enemy, y + 2, _enemies, _players);
	  }

	  if (enemy->hasToShot()) {
	    PaquetPlayerShot shot(enemy);
	    this->broadcast(_players, shot);
	    enemy->addBullet(std::make_shared<Bullet>(shot.getX(), shot.getY(), shot.getSpeed(), shot.getType()));
	  }
	}

	if (changed) {
	  this->updateEnemy(enemy);
	}

	auto &bullets = enemy->getBullets();

	Physics::Bullet = 1;
	for (auto &bullet : bullets) {

	  if (bullet->getType()) {

	    uint16_t y = bullet->getY();
	    uint16_t x = bullet->getX();

	    auto focused = this->focusOnClosestPlayer(y);

	    uint16_t distanceX = 0xFFFF;

	    if (focused->getPosition().x < x) {
	      distanceX = x - focused->getPosition().x;
	    }

	    if (focused && focused->getPosition().y < y) {
	      if (distanceX < 100) {
		bullet->getY() -= 5;
	      }
	      else if (distanceX < 400) {
		bullet->getY() -= 3;
	      }
	    }
	    else if (focused && focused->getPosition().y > y) {
	      if (distanceX < 100) {
		bullet->getY() += 5;
	      }
	      if (distanceX < 400) {
		bullet->getY() += 3;
	      }
	    }
	  }

	  bullet->setX(bullet->getX() - static_cast<uint16_t>((bullet->getSpeed() * _timerBullet->secFloat())));
	  if (Physics::isContact(Physics::LOCK, bullet, _players)) {
	    uint8_t id = Physics::idContact;
	    auto &&player = _players.findIn([id] (auto &p) { return (p->getID() == id); });

	    int life = static_cast<int>(player->getLife()) - 7;
	    if (life < 0) {
	      life = 0;
	    }

	    player->setLife(life);
	    PaquetLife	paquet(player);
	    this->broadcast(_players, paquet);

	    if (life <= 0) {
	      PaquetDeath paquet(player);
	      this->broadcast(_players, paquet);
	    }

	    bullet->setID(0xFF);
	  }
	}
	Physics::Bullet = 0;

	bullets.remove_if([] (auto &b) { return (b->getX() > 2000 || b->getID() == 0xFF); });

      });


    _players.for_each([this] (auto &player) {
	auto &bullets = player->getBullets();

	Physics::Bullet = 1;
	for (auto &bullet : bullets) {
	  bullet->setX(bullet->getX() + static_cast<uint16_t>((bullet->getSpeed() * _timerBullet->secFloat())));
	  if (Physics::isContact(Physics::LOCK, bullet, _enemies)) {
	    uint8_t id = Physics::idContact;
	    auto &&enemy = _enemies.findIn([id] (auto &p) { return (p->getID() == id); });

	    int life = static_cast<int>(enemy->getLife()) - 10;
	    if (life < 0) {
	      life = 0;
	    }

	    enemy->setLife(life);
	    PaquetLife	paquet(enemy);
	    this->broadcast_nolock(_players, paquet);

	    if (life <= 0) {
	      PaquetDeath paquet(enemy);
	      this->broadcast_nolock(_players, paquet);
	      enemy->setID(0xFF);
	    }

	    bullet->setID(0xFF);
	  }
	}
	Physics::Bullet = 0;

	bullets.remove_if([] (auto &b) { return (b->getX() > 1500 || b->getID() == 0xFF); });

      });

    _bonusmalus.for_each([this] (auto &bonus) {

	bonus->setX(bonus->getX() - static_cast<uint16_t>((bonus->getSpeed() * _timerBullet->secFloat())));

	if (Physics::isContact(Physics::LOCK, bonus, _players)) {

	  uint8_t id = Physics::idContact;

	  auto &&player = _players.findIn([id] (auto &p) { return (p->getID() == id); });

	  if (player) {
	    PaquetAttrBonus paquet(player);

	    paquet.setBonusType(bonus->getType());
	    paquet.setTime(7 * 1000);
	    paquet.createPaquet();

	    this->write(paquet, player->addr());
	  }

	  bonus->setID(0xFF);
	}

      });

    _bonusmalus.remove_if([] (auto &b) { return (b->getID() == 0xFF); });
    _enemies.remove_if([] (auto &e) { return (e->getID() == 0xFF); });

    _timerBullet->reset();
    IOEvent::wait(20);
  }
}

const Player_SharedPtr	Party::focusOnClosestPlayer(const uint16_t yEnemy) const
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

bool			Party::addPlayer(const Player_SharedPtr player)
{
  if (_running == false && _players.size() < 4) {
    _players.emplace_back(player);
    return (true);
  }
  return (false);
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

Player_SharedPtr	Party::playerLeave(const uint8_t id)
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

bool			Party::isPlayer(const uint8_t id) const
{
  return (_players.findIn([id] (auto &p) { return (p->getID() == id); }) != nullptr);
}

void			Party::setCoordPlayer(const uint8_t id, const uint16_t x, const uint16_t y)
{
  auto &&player = _players.findIn([id] (auto &p) { return (p->getID() == id); });
  PaquetPlayerCoord	paquet;

  if (player) {

    if (Physics::move(Physics::LOCK, player, x, y, _players, _enemies) == false) {
      paquet = player;
      write(paquet, player->addr());
    }
  }
}

void			Party::setReady(const uint8_t id, const uint8_t status)
{
  auto &&player = _players.findIn([&id](auto &p) { return (p->getID() == id); });
  if (player) {
    player->setReady((status) ? (true) : (false));
  }
}

void			Party::setPlayerShot(const uint8_t id, const uint16_t x, const uint16_t y, const uint16_t speed, const uint8_t type)
{
  auto &&player = _players.findIn([id] (auto &p) { return (p->getID() == id); });
  if (player) {
    player->addBullet(std::make_shared<Bullet>(x, y, speed, type));
  }
}

bool			Party::isRunning() const
{
  return (_running);
}

void			Party::setRunning(const bool run)
{
  _running = run;
  if (run == true) {
    Position pos;
    int i = 1;

    _players.for_each([&] (auto &player) {
	pos = player->getPosition();
	pos.y += 100 + 100 * i;
	i += 1;
	player->setPosition(pos);
      });

    _players.for_each([&] (auto &player) {

	PaquetPlayerCoord paquet(player);

	this->write(paquet, player->addr());

      });
    _thread->run([this](void *) -> void * { this->run(); return (0); }, 0);
  }
}

bool			Party::addEnemy(const Enemy_SharedPtr &enemy)
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
	&& _enemies.findIn([id] (auto &e) { return (e->getID() == id); }) == nullptr
	&& _bonusmalus.findIn([id] (auto &bm) { return (bm->getID() == id); }) == nullptr) {
      return (id);
    }
  }
  return (0xFF);
}

bool			Party::addBonusMalus(const BonusMalus_SharedPtr &bm)
{
  if (bm) {
    _bonusmalus.push_back(bm);
    return true;
  }
  return false;
}

void			Party::renamePlayer(const uint8_t id, const std::string &&name)
{
  auto &&player = _players.findIn([id] (auto &p) { return (p->getID() == id); });

  if (player) {
    player->setName(name);
  }
}
