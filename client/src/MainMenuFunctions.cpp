#include "MainMenuFunctions.hh"

MainMenu::MainMenu(IGraphicEngine *eng)
{
	engine = eng;
	currentPage = 0;
}

void MainMenu::changedMenu()
{
	engine->eraseButton("Refresh");
	engine->eraseButton("Join");
	engine->eraseButton("Info");
}

int MainMenu::getCurrentPage()
{
	return currentPage;
}


void MainMenu::setDisplayOnline()
{
	currentPage = 1;
	changedMenu();
	DEBUG_MSG("Set Current Page to Online");
}

void MainMenu::setDisplayOffline()
{
	currentPage = 4;
	changedMenu();
	DEBUG_MSG("Set Current Page to Offline");
}

void MainMenu::setDisplayOption()
{
	currentPage = 3;
	changedMenu();
	DEBUG_MSG("Set Current Page to Option");
}

void MainMenu::myexit()
{
	DEBUG_MSG("Exit");
	exit(EXIT_SUCCESS);
}
