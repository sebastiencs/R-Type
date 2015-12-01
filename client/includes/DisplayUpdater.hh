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

class MainMenu;
class OnlineMenu;
class NetworkClient;

class DisplayUpdater {
public:
	DisplayUpdater(Packager *_packager, NetworkClient *net);
	~DisplayUpdater();

	IGraphicEngine *getGraphicEngine();

	const Packager *getPackager();

	void mainMenu();
	void game();

private:
	IGraphicEngine *graphicEngine;
	NetworkClient *net;
	Packager *packager;
	MainMenu *mainmenu;
	OnlineMenu *onlineMenu;

	std::list<Button* > buttons;
};

#endif /* !DISPLAYUPDATER_HH */
