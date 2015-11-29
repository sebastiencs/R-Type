#include "MainMenu.hh"

MainMenu::MainMenu(IGraphicEngine *eng)
{
	engine = eng;
	currentPage = 0;

	Transformation transformation(50, 200);
	transformation.setScale((float)0.35, (float)0.2);
	std::function<void()> fptr;
	fptr = std::bind(&MainMenu::setDisplayOnline, this);
	buttons.push_back(new Button("Online", "onlineButton.png", transformation, Color::None, fptr, "Online", eng));

	transformation.setPosition(50, 300);
	fptr = std::bind(&MainMenu::setDisplayOffline, this);
	buttons.push_back(new Button("Offline", "offlineButton.png", transformation, Color::None, fptr, "Offline", eng));

	transformation.setPosition(50, 400);
	fptr = std::bind(&MainMenu::setDisplayOption, this);
	buttons.push_back(new Button("Option", "optionButton.png", transformation, Color::None, fptr, "Option", eng));

	transformation.setPosition(50, 500);
	fptr = std::bind(&MainMenu::myexit, this);
	buttons.push_back(new Button("Exit", "exitButton.png", transformation, Color::None, fptr, "Exit", eng));

	fptr = std::bind(&MainMenu::draw, this);
	eng->setCallbackFunction(fptr, this);
}

void MainMenu::changedMenu()
{
	// If button exist, erase it
	engine->eraseButton("Refresh");
	engine->eraseButton("Join");
	engine->eraseButton("Info");
}

int MainMenu::getCurrentPage()
{
	return currentPage;
}

void MainMenu::draw()
{
	for (Button* b : buttons)
		b->draw();

	/*if (currentPage == 1)
		onlineMenu->menu();*/
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
