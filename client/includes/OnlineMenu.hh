#ifndef ONLINE_MENU_HH_
# define ONLINE_MENU_HH_

# include "DisplayUpdater.hh"
# include "ScrollView.hh"
# include "Packager.hh"
#include "CreateGameMenu.hh"

class CreateGameMenu;

class OnlineMenu {
public:
	OnlineMenu(IGraphicEngine* eng);
	~OnlineMenu();

	void menu();
	void createRequestPartiesPaquet();

	void draw();

	void onClick(uint32_t x, uint32_t y);
	void onHover(uint32_t x, uint32_t y);

	// Join Button
	void joinButton();
	void backButton();
	void createButton();

private:
	IGraphicEngine *engine;
	ScrollView *scrollView;

	std::list<Button* > buttons;
	CreateGameMenu *createGameMenu;
};

#endif // !ONLINE_MENU_HH_
