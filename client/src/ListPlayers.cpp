#include "ListPlayers.hh"
#include "Debug.hh"

ListPlayers & ListPlayers::getInstance()
{
	static ListPlayers_SharedPtr instance = nullptr;
	if (instance == nullptr) {
		instance = std::make_shared<ListPlayers>();
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

void ListPlayers::addPlayer(Player_SharedPtr &&player)
{
	listPlayers.push_back(player);
}

void ListPlayers::deletePlayer(uint8_t id)
{
  listPlayers.remove_if([this, id] (auto &p) {
      if (p->getID() == id) {
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
	listPlayers.remove_if([this](auto &p) {
	    if (p->getID() != _id) {
	      return (true);
	    }
	    else {
	      return (false);
	    }
	  });
}

bool ListPlayers::isEmpty()
{
	return listPlayers.empty();
}

const ListSecure<Player_SharedPtr>& ListPlayers::getListPlayers() const
{
	return listPlayers;
}

Player_SharedPtr ListPlayers::getPlayer(uint8_t id)
{
	for (auto &p : listPlayers)
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
