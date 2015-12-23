#ifndef ONLINE_MENU_HH_
# define ONLINE_MENU_HH_

# include <chrono>
# include <thread>
# include "DisplayUpdater.hh"
# include "ScrollView.hh"
# include "Packager.hh"
# include "LobbyMenu.hh"
# include "IOEvent.hh"
# include "CreateGameMenu.hh"
# include "Box.hh"
# include "Cell.hh"

class CreateGameMenu;
class LobbyMenu;

using CreateGameMenu_SharedPtr = std::shared_ptr<CreateGameMenu>;

class OnlineMenu : public std::enable_shared_from_this<OnlineMenu>
{
public:
	OnlineMenu(IGraphicEngine_SharedPtr eng);
	~OnlineMenu();

	void menu();
	void createRequestPartiesPaquet();

	void setPartyListUpdate(bool changed);

	void draw();
	void onCreateGame();
	bool onClick(uint32_t x, uint32_t y);
	void onHover(uint32_t x, uint32_t y);

	// Join Button
	void joinButton();
	void backButtonGameMenu();
	void backButtonLobbyMenu();
	void createButton();

private:
	IGraphicEngine_SharedPtr engine;
	LobbyMenu_SharedPtr lobby;
	CreateGameMenu_SharedPtr createGameMenu;
	IThread_SharedPtr threadReceivedParties;
	int cond;

	ScrollView_SharedPtr scrollView;
	Box_SharedPtr onlineChoiseBox;

	std::list<Button* > buttons;
	std::list<PartyNB> games;

	bool partyListUpdate;
	bool inLobby;
};

#endif // !ONLINE_MENU_HH_
