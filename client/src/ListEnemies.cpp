#include "ListEnemies.hh"
#include "Debug.hh"
#include "Tools.hh"

ListEnemies::ListEnemies()
{
  DEBUG_MSG("ListEnemy Constructed");
}

ListEnemies::~ListEnemies()
{
  DEBUG_MSG("ListEnemy deleted");
}

void ListEnemies::addEnemy(Enemy_SharedPtr enemy)
{
  _enemies.push_back(enemy);
}

void		ListEnemies::handleEnnemy(const uint8_t id, const uint8_t life, const uint8_t type, const uint16_t x, const uint16_t y)
{
  Enemy_SharedPtr	e;

  if ((e = getEnemy(id)) == nullptr) {
    e = std::make_shared<Enemy>(id, life, type);
    addEnemy(e);
  }
  e->setX(x);
  e->setY(y);
}

void ListEnemies::deleteEnemy(const uint8_t id)
{
  _enemies.remove_if([this, id] (auto &e) {
      if (e->getID() == id) {
	DEBUG_MSG("One enemy deleted");
	return (true);
      }
      else {
	return (false);
      }
    });
}

void ListEnemies::clearList()
{
  _enemies.clear();
}

const ListSecure<Enemy_SharedPtr> &ListEnemies::getListEnemies() const
{
  return _enemies;
}

ListSecure<Enemy_SharedPtr> &ListEnemies::getListEnemies()
{
  return _enemies;
}

Enemy_SharedPtr ListEnemies::getEnemy(const uint8_t id)
{
  return (_enemies.findIn([id] (auto &e) { return (e->getID() == id); }));
}
