#include "DisplayUpdater.hh"


DisplayUpdater::DisplayUpdater(Packager * _packager)
{
	packager = _packager;
	graphicEngine = new GraphicEngine(packager);
	mainmenu = new MainMenu(graphicEngine);
	/*onlineMenu = new OnlineMenu(graphicEngine, packager);

	graphicEngine->createWindow(800, 600, "R-Type");
	
	Transformation transformation(50, 200);
	transformation.setScale((float)0.35, (float)0.2);
	std::function<void()> fptr;
	fptr = std::bind(&MainMenu::setDisplayOnline, this->mainmenu);
	buttons.push_back(new Button("Online", "onlineButton.png", transformation, Color::None, fptr, "Online", graphicEngine));
	
	transformation.setPosition(50, 300);
	fptr = std::bind(&MainMenu::setDisplayOffline, this->mainmenu);
	buttons.push_back(new Button("Offline", "offlineButton.png", transformation, Color::None, fptr, "Offline", graphicEngine));

	transformation.setPosition(50, 400);
	fptr = std::bind(&MainMenu::setDisplayOption, this->mainmenu);
	buttons.push_back(new Button("Option", "optionButton.png", transformation, Color::None, fptr, "Option", graphicEngine));

	transformation.setPosition(50, 500);
	fptr = std::bind(&MainMenu::myexit, this->mainmenu);
	buttons.push_back(new Button("Exit", "exitButton.png", transformation, Color::None, fptr, "Exit", graphicEngine));*/

	/*fptr = std::bind(&DisplayUpdater::mainMenu, this); 
	graphicEngine->setCallbackFunction(fptr, this);*/

	graphicEngine->launch();
}

DisplayUpdater::~DisplayUpdater()
{
	for (Button* b : buttons)
		delete b;
	buttons.clear();
}

const Packager * DisplayUpdater::getPackager()
{
	return packager;
}

IGraphicEngine * DisplayUpdater::getGraphicEngine()
{
	return graphicEngine;
}

void DisplayUpdater::mainMenu()
{
	for (Button* b : buttons)
		b->draw();

	if (mainmenu->getCurrentPage() == 1)
		onlineMenu->menu();
}

void DisplayUpdater::game()
{
	//while (PackageStorage::getInstance().getObstaclesPackage() != nullptr) {
	//	const PaquetObstacle* p = PackageStorage::getInstance().getObstaclesPackage();
	//	graphicEngine->drawImage(obstacleTypeToSpriteString[p->getType()], Transformation(p->getX(), p->getY()));
	//	PackageStorage::getInstance().deleteObstaclesPackage();
	//}
	//while (PackageStorage::getInstance().getPlayersPackage() != nullptr) {
	//	const PaquetPlayerCoord* p = PackageStorage::getInstance().getPlayersPackage();
	//	graphicEngine->drawImage(playerIDToSpriteString[p->getPlayerID()], Transformation(p->getX(), p->getY()));
	//	PackageStorage::getInstance().deletePlayersPackage();
	//}
	//while (PackageStorage::getInstance().getShotsPackage() != nullptr) {
	//	const PaquetPlayerShot* p = PackageStorage::getInstance().getShotsPackage();
	//	graphicEngine->drawImage(shotTypeToSpriteString[p->getType()], Transformation(p->getX(), p->getY()));
	//	PackageStorage::getInstance().deleteShotsPackage();
	//}
}
