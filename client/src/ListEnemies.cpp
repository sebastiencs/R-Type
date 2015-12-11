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

void ListEnemies::addEnemy(Enemy* enemy)
{
  _enemies.push_back(enemy);
}

void		ListEnemies::handleEnnemy(uint8_t id, uint8_t life, uint8_t type, uint16_t x, uint16_t y)
{
  Enemy		*e;

  if ((e = getEnemy(id)) == nullptr) {
    e = new Enemy(id, life, type);
    addEnemy(e);
  }
  e->setPosX(x);
  e->setPosY(y);
}

void ListEnemies::deleteEnemy(uint8_t id)
{
  _enemies.remove_if([this, id] (auto &e) {
      if (e->getID() == id) {
	delete e;
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

const ListSecure<Enemy*> &ListEnemies::getListEnemies() const
{
  return _enemies;
}

Enemy* ListEnemies::getEnemy(uint8_t id)
{
  return (Tools::findIn(_enemies, [id] (auto &e) { return (e->getID() == id); }));
}
