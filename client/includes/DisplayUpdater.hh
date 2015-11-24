#ifndef DISPLAYUPDATER_HH
#define DISPLAYUPDATER_HH

#include "Packager.hh"
#include "PackageStorage.hh"
#include "IGraphicEngine.hh"
#include "GraphicEngine.hh"

class DisplayUpdater {
public:
	DisplayUpdater(Packager *_packager);
	~DisplayUpdater();

	void inMenu();
	void inGame();

	const Packager *getPackager();
	IGraphicEngine *getGraphicEngine();

private:
	Packager *packager;
	IGraphicEngine *graphicEngine;
};

void mainMenu(void *arg);
void game(void *arg);

#endif