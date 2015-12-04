#ifndef ONLINE_MENU_HH_
# define ONLINE_MENU_HH_

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

class OnlineMenu {
public:
	OnlineMenu(IGraphicEngine* eng);
	~OnlineMenu();

	void menu();
	void createRequestPartiesPaquet();

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
	IGraphicEngine *engine;
	LobbyMenu *lobby;
	CreateGameMenu *createGameMenu;
	IThread *threadReceivedParties;

	ScrollView *scrollView;
	Box *onlineChoiseBox;

	std::list<Button* > buttons;

	bool inLobby;
};

#endif // !ONLINE_MENU_HH_
