#include "ListPlayers.hh"
#include "Debug.hh"

ListPlayers & ListPlayers::getInstance()
{
	static ListPlayers *instance = nullptr;
	if (instance == nullptr) {
		instance = new ListPlayers();
	}
	return *instance;
}

ListPlayers::ListPlayers()
{
  DEBUG_MSG("ListPlayer Constructed");
}

ListPlayers::~ListPlayers()
{
  DEBUG_MSG("ListPlayer deleted");
}

ListPlayers::ListPlayers(const ListPlayers &)
{
  DEBUG_MSG("ListPlayer Copied");
}

ListPlayers &ListPlayers::operator=(const ListPlayers &)
{
  DEBUG_MSG("ListPlayer attributed");
  return (*this);
}

void ListPlayers::addPlayer(Player* player)
{
	listPlayers.push_back(player);
}

void ListPlayers::deletePlayer(uint8_t id)
{
  listPlayers.remove_if([this, id] (auto &p) {
      if (p->getID() == id) {
	delete p;
	DEBUG_MSG("One player deleted");
	return (true);
      }
      else {
	return (false);
      }
    });
}

void ListPlayers::clearList()
{
	listPlayers.remove_if([this](Player *p) {
	    if (p->getID() != _id) {
	      delete p;
	      return (true);
	    }
	    else {
	      return (false);
	    }
	  });
}

const ListSecure<Player*>& ListPlayers::getListPlayers() const
{
	return listPlayers;
}

Player* ListPlayers::getPlayer(uint8_t id)
{
	for (Player *p : listPlayers)
		if (p->getID() == id)
			return p;
	return nullptr;
}

uint8_t ListPlayers::getId() const
{
	return _id;
}

void ListPlayers::setId(uint8_t id)
{
	_id = id;
  listPlayers.front()->setID(id);
}
