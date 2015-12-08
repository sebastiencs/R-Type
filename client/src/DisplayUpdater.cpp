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

	t.setScale(3.5, 3.5);
	if (PackageStorage::getInstance().getObstaclesPackage() != nullptr) {
		//const PaquetObstacle* p = PackageStorage::getInstance().getObstaclesPackage();

		//graphicEngine->drawImage(obstacleTypeToSpriteString[p->getType()], Transformation(p->getX(), p->getY()));
		//PackageStorage::getInstance().deleteObstaclesPackage();
	}
	if (PackageStorage::getInstance().getShotsPackage() != nullptr) {
		const PaquetPlayerShot* p = PackageStorage::getInstance().getShotsPackage();
		Player *player = LP.getPlayer(p->getPlayerID());
		player->addBullet(new Position(p->getX(), p->getY()));
		PackageStorage::getInstance().deleteShotsPackage();
	}
	if (PackageStorage::getInstance().getPlayersPackage() != nullptr) {
		const PaquetPlayerCoord* p = PackageStorage::getInstance().getPlayersPackage();
		Position L(p->getX(), p->getY());
		LP.getPlayer(p->getPlayerID())->setPosition(L);
		PackageStorage::getInstance().deletePlayersPackage();
	}
	// TODO: corriger les pos de la bullet
	int i = 0;
	for (Player *player : LP.getListPlayers()) {
		Transformation t(player->getPosition().x, player->getPosition().y);
		if (!player->getBullets().empty()) {
			for (Position *bullet : player->getBullets()) {
				graphicEngine->drawImage("bullet1.png", Transformation(bullet->x, bullet->y));
				bullet->x += 15;
			}

			int windowWidth = getGraphicEngine()->getWindowWidth();
			auto clearFunc = [windowWidth](Position *elem) {
				DEBUG_MSG("bulletX: " << elem->x << "window: " << windowWidth);
				if (elem->x > windowWidth) {
					delete elem;
					return true;
				}
				return false;
			};
			std::list<Position* >& bulletList = const_cast<std::list<Position* >& >(player->getBullets());
			bulletList.remove_if(clearFunc);
		}

		t.setScale(3.5, 3.5);
		graphicEngine->drawImage("vessel" + std::to_string(i++) + ".png", t);
	}
}
