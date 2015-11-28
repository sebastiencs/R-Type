#include "DisplayUpdater.hh"


DisplayUpdater::DisplayUpdater(Packager * _packager)
{
	packager = _packager;
	graphicEngine = new GraphicEngine(packager);
	graphicEngine->createWindow(800, 600, "R-Type");
	std::function<void(void *)> test = std::bind(&DisplayUpdater::mainMenuTest, this, nullptr); 
	graphicEngine->setCallbackFunction(test, this);
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

void DisplayUpdater::mainMenuTest(void *arg)
{
	//DisplayUpdater *tmp = static_cast<DisplayUpdater *>(arg);
	//IGraphicEngine* engine = tmp->getGraphicEngine();
	Transformation t1(50, 200);

	graphicEngine->drawText("R-Type", Transformation(50, graphicEngine->getWindowHeight() / 5), 42, Color::White, "Fipps.otf");

	t1.setScale((float)0.35, (float)0.2);
	graphicEngine->displayButton("Online", "onlineButton.png", t1, Color::None, &setDisplayOnline);
	t1.setPosition(50, 300);
	graphicEngine->displayButton("Offline", "offlineButton.png", t1, Color::None, &setDisplayOffline);
	t1.setPosition(50, 400);
	graphicEngine->displayButton("Option", "optionButton.png", t1, Color::None, &setDisplayOption);
	t1.setPosition(50, 500);
	graphicEngine->displayButton("Exit", "exitButton.png", t1, Color::None, &myexit);

	/*t1.setScale((float)0.35, (float)0.2);
	graphicEngine->displayButton("Online", "onlineButton.png", t1, Color::None, &setDisplayOnline, arg);
	t1.setPosition(50, 300);
	graphicEngine->displayButton("Offline", "offlineButton.png", t1, Color::None, &setDisplayOffline, arg);
	t1.setPosition(50, 400);
	graphicEngine->displayButton("Option", "optionButton.png", t1, Color::None, &setDisplayOption, arg);
	t1.setPosition(50, 500);
	graphicEngine->displayButton("Exit", "exitButton.png", t1, Color::None, &myexit);*/
	/*if (currentPageMenu == 1)
		onlineMenu(arg);
	else {
		graphicEngine->eraseButton("t1");
		graphicEngine->eraseButton("t2");
		graphicEngine->eraseButton("t3");
		graphicEngine->eraseButton("t4");*/
	//}
}


void mainMenu(void *arg) {
	DisplayUpdater *tmp = static_cast<DisplayUpdater *>(arg);
	IGraphicEngine* engine = tmp->getGraphicEngine();
	Transformation t1(50, 200);

	engine->drawText("R-Type", Transformation(50, engine->getWindowHeight() / 5), 42, Color::White, "Fipps.otf");

	t1.setScale((float)0.35, (float)0.2);
	engine->displayButton("Online", "onlineButton.png", t1, Color::None, &setDisplayOnline, arg);
	t1.setPosition(50, 300);
	engine->displayButton("Offline", "offlineButton.png", t1, Color::None, &setDisplayOffline, arg);
	t1.setPosition(50, 400);
	engine->displayButton("Option", "optionButton.png", t1, Color::None, &setDisplayOption, arg);
	t1.setPosition(50, 500);
	engine->displayButton("Exit", "exitButton.png", t1, Color::None, &myexit);
	if (tmp->getCurrentPageMenu() == 1)
		onlineMenu(arg);
	else {
		engine->eraseButton("t1");
		engine->eraseButton("t2");
		engine->eraseButton("t3");
		engine->eraseButton("t4");
	}
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

