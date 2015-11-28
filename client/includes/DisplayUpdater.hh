#ifndef DISPLAYUPDATER_HH
#define DISPLAYUPDATER_HH

#include "Packager.hh"
#include "PackageStorage.hh"
#include "IGraphicEngine.hh"
#include "GraphicEngine.hh"
#include "MainMenuFunctions.hh"
#include "OnlineMenuFunctions.hh"

class DisplayUpdater {
public:
	DisplayUpdater(Packager *_packager);
	~DisplayUpdater();

	void inMenu();
	void inGame();

	const Packager *getPackager();
	int getCurrentPageMenu() const;
	void setCurrentPageMenu(int page);

	IGraphicEngine *getGraphicEngine();

	void mainMenu();

private:
	Packager *packager;
	IGraphicEngine *graphicEngine;
	int currentPageMenu;
};

//void mainMenu(void *arg);
void game(void *arg);

#endif
