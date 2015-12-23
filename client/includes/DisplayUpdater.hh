#ifndef DISPLAYUPDATER_HH
# define DISPLAYUPDATER_HH

# include "Packager.hh"
# include "NetworkClient.hh"
# include "PackageStorage.hh"
# include "IGraphicEngine.hh"
# include "GraphicEngine.hh"
# include "MainMenu.hh"
# include "Credits.hh"
# include "OnlineMenu.hh"
# include "ListPlayers.hh"
# include "TaskScheduler.hh"
# include "Mutex.hh"
# include "Text.hh"
# include "Sprite.hh"

class MainMenu;
class OnlineMenu;
class NetworkClient;
class Game;

class DisplayUpdater {
public:
	DisplayUpdater(Packager_SharedPtr _packager, NetworkClient_SharedPtr net);
	~DisplayUpdater();

	IGraphicEngine_SharedPtr getGraphicEngine();

	void mainMenu();
	void game();
	void launchObserver();

private:
	IGraphicEngine_SharedPtr graphicEngine;
	Packager_SharedPtr packager;
	NetworkClient_SharedPtr net;
	MainMenu_SharedPtr mainmenu;
	OnlineMenu_SharedPtr onlineMenu;
	TaskScheduler *launchLoop;
	bool inGame;

	IThread *threadGame;
	ListSecure<Text *> _nickname;
	ListSecure<Sprite *> images;
	int cond;
	Game *_game;
	bool dead;
	ITimer* deathTimer;

	int32_t xBg1;
	int32_t xBg2;
	Sprite_SharedPtr bg1;
	Sprite_SharedPtr bg2;
	Transformation tBg1;
	Transformation tBg2;
};

#endif /* !DISPLAYUPDATER_HH */
