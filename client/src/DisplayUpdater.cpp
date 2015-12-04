#include "DisplayUpdater.hh"
#include "ListPlayers.hh"


DisplayUpdater::DisplayUpdater(Packager * _packager, NetworkClient *net)
{
	packager = _packager;
	graphicEngine = new GraphicEngine(packager);
	mainmenu = new MainMenu(graphicEngine, net);
	this->net = net;

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

	if (!net->getIsConnect())
		graphicEngine->drawText("You are not connected", Transformation(800, 50), 12, Color::Red, "Fipps.otf");

	PackageStorage& PC = PackageStorage::getInstance();
	const PaquetResponse *paquet = PC.getAnswersPackage();
	if (paquet) {
		ListPlayers list = ListPlayers::getInstance();
		if (paquet->getReturn() == 2)
				list.getListPlayers().front()->setID(paquet->getData());
				list.setId(paquet->getData());
				std::cout << "------------> ID : " << list.getId() << std::endl;
	}
}

void DisplayUpdater::game()
{
	Transformation t;
	t.setBounds(1024, 768);
	t.setPosition(0, 0);
	Sprite *bg = new Sprite("", t, graphicEngine, Color::Red);
	bg->draw();
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
