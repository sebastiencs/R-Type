#ifndef LIST_PLAYERS_HH_
# define LIST_PLAYERS_HH_

# include <iostream>
# include <list>
# include "Player.hh"
# include "ListSecure.hh"

class		ListPlayers
{
public:
	static ListPlayers& getInstance();

	ListPlayers();
	ListPlayers(const ListPlayers &);

	ListPlayers &operator=(const ListPlayers &);

	virtual ~ListPlayers();

	void addPlayer(Player_SharedPtr &&player);
	void clearList();
	bool isEmpty();

	void deletePlayer(const uint8_t id);

	const ListSecure<Player_SharedPtr> &getListPlayers() const;
	Player_SharedPtr getPlayer(const uint8_t id);
	uint8_t getId() const;
	void setId(const uint8_t id);

private:
 ListSecure<Player_SharedPtr> listPlayers;
 uint8_t _id;
};

typedef std::shared_ptr<ListPlayers> ListPlayers_SharedPtr;

#endif /* !LIST_PLAYERS_HH_ */
