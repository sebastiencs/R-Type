#ifndef DISPLAYUPDATER_HH
#define DISPLAYUPDATER_HH

#include "Packager.hh"
#include "PackageStorage.hh"
#include "IGraphicEngine.hh"
#include "GraphicEngine.hh"
#include "MainMenuFunctions.hh"
#include "OnlineMenuFunctions.hh"

class MainMenu;
class OnlineMenu;

class DisplayUpdater {
public:
	DisplayUpdater(Packager *_packager);
	~DisplayUpdater();

	void inMenu();
	void inGame();

	const Packager *getPackager();

	IGraphicEngine *getGraphicEngine();

	void mainMenu();

private:
	IGraphicEngine *graphicEngine;
	Packager *packager;
	MainMenu *mainmenu;
	OnlineMenu *onlineMenu;
};

//void mainMenu(void *arg);
void game(void *arg);

#endif
