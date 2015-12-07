#include "DisplayUpdater.hh"


DisplayUpdater::DisplayUpdater(Packager * _packager, NetworkClient *net)
{
	packager = _packager;
	graphicEngine = new GraphicEngine(packager);
	mainmenu = new MainMenu(graphicEngine, net);
	this->net = net;
	Callback_t fptr = [this](void *) {this->launchObserver(); return nullptr; };
	launchLoop = new TaskScheduler(fptr, 50);

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
	delete launchLoop;
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

	if (!net->getIsConnect())
		graphicEngine->drawText("You are not connected", Transformation(800, 50), 12, Color::Red, "Fipps.otf");
}

void DisplayUpdater::launchObserver()
{
	static const PaquetLaunch *launch = nullptr;
	static PackageStorage& ps = PackageStorage::getInstance();
	launch = ps.getLaunchPackage();
	if (launch != nullptr) {
		callback fptr = std::bind(&DisplayUpdater::game, this);
		graphicEngine->setCallbackFunction(fptr, nullptr);
		delete launch;
		launchLoop->stop();
	}
}

void DisplayUpdater::game()
{
	ListPlayers &LP = ListPlayers::getInstance();
	Transformation t;
	t.setBounds(1024, 768);
	t.setPosition(0, 0);
	Sprite *bg = new Sprite("menubackground8bit.png", t, graphicEngine, Color::None);
	bg->draw();

	if (PackageStorage::getInstance().getObstaclesPackage() != nullptr) {
		const PaquetObstacle* p = PackageStorage::getInstance().getObstaclesPackage();
		//graphicEngine->drawImage(obstacleTypeToSpriteString[p->getType()], Transformation(p->getX(), p->getY()));
		PackageStorage::getInstance().deleteObstaclesPackage();
	}
	if (PackageStorage::getInstance().getShotsPackage() != nullptr) {
		const PaquetPlayerShot* p = PackageStorage::getInstance().getShotsPackage();
		//graphicEngine->drawImage(shotTypeToSpriteString[p->getType()], Transformation(p->getX(), p->getY()));
		PackageStorage::getInstance().deleteShotsPackage();
	}
	if (PackageStorage::getInstance().getPlayersPackage() != nullptr) {
		const PaquetPlayerCoord* p = PackageStorage::getInstance().getPlayersPackage();
		Position L(p->getX(), p->getY());
		LP.getPlayer(p->getPlayerID())->setPosition(L);
		PackageStorage::getInstance().deletePlayersPackage();
	}
	for (Player *player : LP.getListPlayers())
		graphicEngine->drawImage("vessel" + std::to_string((player->getID() % 4)) + ".png", Transformation(std::get<0>(player->getPosition()), std::get<1>(player->getPosition())));
}

