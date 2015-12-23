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

typedef std::shared_ptr<Game>	Game_SharedPtr;

class DisplayUpdater {
public:
	DisplayUpdater(Packager_SharedPtr _packager, NetworkClient_SharedPtr net);
	~DisplayUpdater();

	IGraphicEngine *getGraphicEngine();

	void mainMenu();
	void game();
	void launchObserver();

private:
	IGraphicEngine *graphicEngine;
	Packager_SharedPtr packager;
	NetworkClient_SharedPtr net;
	MainMenu *mainmenu;
	OnlineMenu *onlineMenu;
	TaskScheduler *launchLoop;
	bool inGame;

	IThread *threadGame;
	ListSecure<Text *> _nickname;
	ListSecure<Sprite *> images;
	int cond;
	Game_SharedPtr _game;
	bool dead;
	ITimer* deathTimer;

	int32_t xBg1;
	int32_t xBg2;
	Sprite_SharedPtr bg1;
	Sprit_SharedPtr bg2;
	Transformation tBg1;
	Transformation tBg2;
};

#endif /* !DISPLAYUPDATER_HH */
