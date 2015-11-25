#include "DisplayUpdater.hh"


DisplayUpdater::DisplayUpdater(Packager * _packager)
{
	packager = _packager;
	graphicEngine = new GraphicEngine(packager);
	graphicEngine->createWindow(800, 600, "R-Type");
	graphicEngine->setCallbackFunction(&game, this);

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

IGraphicEngine * DisplayUpdater::getGraphicEngine()
{
	return graphicEngine;
}

void mainMenu(void *arg) {
	//drawButton("play");
	//drawButton("exit");
}

void buttonListener(void* arg) {
	std::cout << "Clicked" << std::endl;
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

	engine->drawImage("r-typesheet26.gif", Transformation(0, 0));
	/* test */
	static unsigned int i = 0;
	Transformation t(100, 100);
	if (i > 6) {
		i = 0;
	}
	t.setCrop(i * 33, 0, 33, 33);
	engine->drawSplitImage("r-typesheet23.gif", t, Color::None);
	t.setPosition(150, 100);
	t.setCrop(i * 33, 33, 33, 33);
	engine->drawSplitImage("r-typesheet23.gif", t, Color::None);
	i++;
	engine->drawText("DefaultText", Transformation(50, 50), DEFAULT_FONT_SIZE);
	engine->drawText("OtherText", Transformation(80, 80), 20, Color::White, "Fipps.otf");

	engine->createButton("Coucou", "Button.png", Transformation(0, 500), Color::None, &buttonListener, nullptr);
}
