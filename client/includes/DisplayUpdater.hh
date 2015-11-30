#ifndef DISPLAYUPDATER_HH
# define DISPLAYUPDATER_HH

# include "Packager.hh"
# include "PackageStorage.hh"
# include "IGraphicEngine.hh"
# include "GraphicEngine.hh"
# include "MainMenu.hh"
# include "OnlineMenu.hh"

class MainMenu;
class OnlineMenu;

class DisplayUpdater {
public:
	DisplayUpdater(Packager *_packager);
	~DisplayUpdater();

	IGraphicEngine *getGraphicEngine();

	const Packager *getPackager();

	void mainMenu();
	void game();

private:
	IGraphicEngine *graphicEngine;
	Packager *packager;
	MainMenu *mainmenu;
	OnlineMenu *onlineMenu;

	std::list<Button* > buttons;
};

#endif /* !DISPLAYUPDATER_HH */
