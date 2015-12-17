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
	DisplayUpdater(Packager *_packager, NetworkClient *net);
	~DisplayUpdater();

	IGraphicEngine *getGraphicEngine();

	const Packager *getPackager();

	void mainMenu();
	void game();
	void launchObserver();

private:
	IGraphicEngine *graphicEngine;
	NetworkClient *net;
	Packager *packager;
	MainMenu *mainmenu;
	OnlineMenu *onlineMenu;
	TaskScheduler *launchLoop;
	bool inGame;

	IThread *threadGame;
  ListSecure<Text *> _nickname;
  ListSecure<Sprite *> images;
	int cond;
	Game *_game;
};

#endif /* !DISPLAYUPDATER_HH */
