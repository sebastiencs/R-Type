#include "DisplayUpdater.hh"
#include "SystemAudio.hh"
#include "Game.hh"
#include "Locker.hh"

DisplayUpdater::DisplayUpdater(Packager * _packager, NetworkClient *net) : inGame(false), cond(1), dead(false)
{
	threadGame = nullptr;
	_game = nullptr;
	deathTimer = nullptr;
	packager = _packager;
	graphicEngine = new GraphicEngine();
	mainmenu = new MainMenu(graphicEngine, net);
	this->net = net;
	Callback_t fptr = [this](void *) {this->launchObserver(); return nullptr; };
	launchLoop = new TaskScheduler(fptr, 50);

	xBg1 = 0;
	tBg1.setPosition(xBg1, 0);
	xBg2 = 1920;
	tBg2.setPosition(xBg2, 0);
	bg1 = new Sprite("ingamebg.png", tBg1, graphicEngine);
	bg2 = new Sprite("ingamebg.png", tBg2, graphicEngine);
	bg1->setId("bg1");
	bg2->setId("bg2");

	graphicEngine->createWindow(1024, 768, "R-Type");
	graphicEngine->launch();
}

DisplayUpdater::~DisplayUpdater()
{
  if (threadGame) {
    cond = 0;
    threadGame->join();
    delete threadGame;
  }
	if (_game)
		delete _game;
	//	delete graphicEngine;   // Problem de thread. Je comprends pas l'erreur. Seb
	if (mainmenu)
		delete mainmenu;
	if (launchLoop)
		delete launchLoop;
	if (deathTimer)
		delete deathTimer;
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
	if (!inGame) {
		if (mainmenu->getCurrentPage() == 1)
			onlineMenu->menu();
	}
}

void DisplayUpdater::launchObserver()
{
	static PackageStorage& ps = PackageStorage::getInstance();
	auto launch = ps.getLaunchPackage();

	if (launch != nullptr) {

		Packager::createFirstUDPPackage(ListPlayers::getInstance().getId());
		Packager::createFirstUDPPackage(ListPlayers::getInstance().getId());

		int width = getGraphicEngine()->getWindowWidth();
		int height = getGraphicEngine()->getWindowHeight();
		_game = new class Game(width, height, images, _nickname, packager);

		inGame = true;
		graphicEngine->setMouseClickCallback(nullptr);	// In game, don't bother to call MainMenu::OnClick
		graphicEngine->setMouseMovedCallback(nullptr);
		usableKeyPressedCallback ptr = std::bind(&Game::handlePlayerMovement, _game, std::placeholders::_1);
		graphicEngine->setUsableKeyPressedCallback(ptr);
		threadGame = new Thread([&](void *) -> void * {
			if (mainmenu != nullptr) {
				delete mainmenu;
				mainmenu = nullptr;
			}
			while (cond) {
				if (_game->run()) {
					dead = true;
					return (nullptr);
				}
			}
			return (nullptr);
		}, nullptr);

		callback fptr = std::bind(&DisplayUpdater::game, this);
		graphicEngine->setCallbackFunction(fptr, nullptr);
		delete launch;
		launchLoop->stop();
	}
}

void DisplayUpdater::game()
{

	//UPDATE THE BACKGROUND
	xBg1 -= (uint32_t)(200 * GraphicEngine::getDeltaTimeS());
	xBg1 = xBg1 < -1920 ? 1920 : xBg1;

	tBg1.setPosition(xBg1, 0);
	bg1->setTransformation(tBg1);
	bg1->draw();
	xBg2 -= (uint32_t)(200 * GraphicEngine::getDeltaTimeS());

	xBg2 = xBg2 < -1920 ? 1920 : xBg2;
	tBg2.setPosition(xBg2, 0);
	bg2->setTransformation(tBg2);
	bg2->draw();


  images.for_each([&](Sprite* img) {
    this->graphicEngine->drawSprite(*img);
    delete img;
  });
  _nickname.for_each([&](Text* text) {
    this->graphicEngine->drawText(*text);
    delete text;
  });

	if (dead) {
		if (deathTimer) {
			Transformation t = Transformation((graphicEngine->getWindowWidth() / 2) - 80, (graphicEngine->getWindowHeight() / 2) - 50);
			Text text = Text("YOU DIED", DEFAULT_FONT, 30, t, graphicEngine, Color(150, 0, 0));
			if (deathTimer->ms() < 7000) {
				graphicEngine->drawText(text);
			}
			else {
				delete deathTimer;
				deathTimer = nullptr;
				dead = false;
			}
		}
		else {
			deathTimer = new Timer();
			deathTimer->start();
		}
	}

	_nickname.clear();
	images.clear();
}
