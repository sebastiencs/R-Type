#include "DisplayUpdater.hh"


DisplayUpdater::DisplayUpdater(Packager * _packager)
{
	packager = _packager;
	graphicEngine = new GraphicEngine(packager);
	graphicEngine->createWindow(800, 600, "R-Type");
	graphicEngine->setCallbackFunction(&mainMenu, this);

	currentPageMenu = 0;
	graphicEngine->launch();
}

DisplayUpdater::~DisplayUpdater()
{
}

void DisplayUpdater::inMenu()
{
	//graphicEngine.setCallBackFunction(&mainMenu, this);
}

void DisplayUpdater::inGame()
{
	//graphicEngine.setCallBackFunction(&game, this);
}

const Packager * DisplayUpdater::getPackager()
{
	return packager;
}

const int DisplayUpdater::getCurrentPageMenu() const
{
	return currentPageMenu;
}

void DisplayUpdater::setCurrentPageMenu(int page)
{
	currentPageMenu = page;
}

IGraphicEngine * DisplayUpdater::getGraphicEngine()
{
	return graphicEngine;
}

void myexit(void *t)
{
	exit(EXIT_SUCCESS);
}

void setDisplayOnline(void *arg)
{
	DisplayUpdater *tmp = static_cast<DisplayUpdater *>(arg);
	tmp->setCurrentPageMenu(1);
}

void mainMenu(void *arg) {
	DisplayUpdater *tmp = static_cast<DisplayUpdater *>(arg);
	IGraphicEngine* engine = tmp->getGraphicEngine();
	Transformation t1(50, 200);

	engine->drawText("R-Type", Transformation(50, engine->getWindowHeight() / 5), 42, Color::White, "Fipps.otf");

	std::cout << tmp->getCurrentPageMenu() << std::endl;
	t1.setScale((float)0.35, (float)0.2);
	engine->displayButton("Online", "Button.png", t1, Color::None, &setDisplayOnline, arg);
	std::cout << tmp->getCurrentPageMenu() << std::endl;
	t1.setPosition(50, 300);
	engine->displayButton("Offline", "Button.png", t1, Color::None, &myexit);
	t1.setPosition(50, 400);
	engine->displayButton("Option", "Button.png", t1, Color::None, &myexit);
	t1.setPosition(50, 500);
	engine->displayButton("Exit", "Button.png", t1, Color::None, &myexit);
}


void game(void *arg) {
	DisplayUpdater *tmp = static_cast<DisplayUpdater *>(arg);
	IGraphicEngine* engine = tmp->getGraphicEngine();

	/*while (PackageStorage::getInstance().getObstaclesPackage() != nullptr) {
		const PaquetObstacle* p = PackageStorage::getInstance().getObstaclesPackage();
		tmp->getGraphicEngine()->drawImage(obstacleTypeToSpriteString[p->getType()], Transformation(p->getX(), p->getY()));
		PackageStorage::getInstance().deleteObstaclesPackage();
	}
	while (PackageStorage::getInstance().getPlayersPackage() != nullptr) {
		const PaquetPlayerCoord* p = PackageStorage::getInstance().getPlayersPackage();
		tmp->getGraphicEngine()->drawImage(playerIDToSpriteString[p->getPlayerID()], Transformation(p->getX(), p->getY()));
		PackageStorage::getInstance().deletePlayersPackage();
	}
	while (PackageStorage::getInstance().getShotsPackage() != nullptr) {
		const PaquetPlayerShot* p = PackageStorage::getInstance().getShotsPackage();
		tmp->getGraphicEngine()->drawImage(shotTypeToSpriteString[p->getType()], Transformation(p->getX(), p->getY()));
		PackageStorage::getInstance().deleteShotsPackage();
	}*/
}

