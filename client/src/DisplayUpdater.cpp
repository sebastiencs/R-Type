#include "DisplayUpdater.hh"


DisplayUpdater::DisplayUpdater(Packager * _packager)
{
	packager = _packager;
	graphicEngine = new GraphicEngine(packager);
	mainmenu = new MainMenu(graphicEngine);

	graphicEngine->createWindow(1024, 768, "R-Type");
	graphicEngine->launch();
}

DisplayUpdater::~DisplayUpdater()
{
	delete graphicEngine;
	delete mainmenu;
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
