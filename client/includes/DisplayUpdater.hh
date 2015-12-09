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

class MainMenu;
class OnlineMenu;
class NetworkClient;
class Game;

typedef struct s_image {
  s_image(std::string _img, Transformation &&_t) : img(_img), t(_t) { }
  s_image(std::string _img, Transformation &_t) : img(_img), t(_t) { }
  std::string img;
  Transformation t;
} Image;

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

	IThread *threadGame;
	std::list<Button* > buttons;
	std::deque<Image> images;
	IMutex *mutex;
	Game *_game;
};

#endif /* !DISPLAYUPDATER_HH */
