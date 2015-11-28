#include "DisplayUpdater.hh"


DisplayUpdater::DisplayUpdater(Packager * _packager)
{
	packager = _packager;
	graphicEngine = new GraphicEngine(packager);
	mainmenu = new MainMenu(graphicEngine);
	onlineMenu = new OnlineMenu(graphicEngine, packager);

	graphicEngine->createWindow(800, 600, "R-Type");

	std::function<void()> fptr = std::bind(&DisplayUpdater::mainMenu, this); 
	graphicEngine->setCallbackFunction(fptr, this);

	graphicEngine->launch();
}

DisplayUpdater::~DisplayUpdater()
{
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
	std::function<void()> fptr;
	Transformation transformation(50, 200);
	transformation.setScale((float)0.35, (float)0.2);

	graphicEngine->drawText("R-Type", Transformation(50, graphicEngine->getWindowHeight() / 5), 42, Color::White, "Fipps.otf");

	fptr = std::bind(&MainMenu::setDisplayOnline, this->mainmenu);
	graphicEngine->displayButton("Online", "onlineButton.png", transformation, Color::None, fptr, "" + 0);

	transformation.setPosition(50, 300);
	fptr = std::bind(&MainMenu::setDisplayOffline, this->mainmenu);
	graphicEngine->displayButton("Offline", "offlineButton.png", transformation, Color::None, fptr, "" + 1);

	transformation.setPosition(50, 400);
	fptr = std::bind(&MainMenu::setDisplayOption, this->mainmenu);
	graphicEngine->displayButton("Option", "optionButton.png", transformation, Color::None, fptr, "" + 2);

	transformation.setPosition(50, 500);
	fptr = std::bind(&MainMenu::myexit, this->mainmenu);
	graphicEngine->displayButton("Exit", "exitButton.png", transformation, Color::None, fptr, "" + 3);

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
