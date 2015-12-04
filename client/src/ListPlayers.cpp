#include "ListPlayers.hh"

ListPlayers & ListPlayers::getInstance()
{
	static ListPlayers *instance;
	if (instance == nullptr) {
		instance = new ListPlayers();
		return *instance;
	}
	else {
		return *instance;
	}
}

ListPlayers::ListPlayers()
{
}

ListPlayers::~ListPlayers()
{
}

void ListPlayers::addPlayer(Player* player)
{
	listPlayers.push_back(player);
}

const std::list<Player*>& ListPlayers::getListPlayers() const
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
}
