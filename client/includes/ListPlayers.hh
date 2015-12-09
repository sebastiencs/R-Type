#ifndef LIST_PLAYERS_HH_
# define LIST_PLAYERS_HH_

# include <iostream>
# include <list>
# include "Player.hh"

class		ListPlayers
{
public:
	static ListPlayers& getInstance();

	ListPlayers();
	ListPlayers(const ListPlayers &);

	ListPlayers &operator=(const ListPlayers &);

	virtual ~ListPlayers();

	void addPlayer(Player* player);
	void clearList();

	void deletePlayer(uint8_t id);

	const std::list<Player *>& getListPlayers() const;
	Player* getPlayer(uint8_t id);
	uint8_t getId() const;
	void setId(uint8_t id);

private:
 std::list<Player *> listPlayers;
 uint8_t _id;
};


#endif /* !LIST_PLAYERS_HH_ */
