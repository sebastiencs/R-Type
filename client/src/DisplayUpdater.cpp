#include "DisplayUpdater.hh"
#include "SystemAudio.hh"
#include "Game.hh"
#include "Locker.hh"

DisplayUpdater::DisplayUpdater(Packager * _packager, NetworkClient *net) : inGame(false)
{
	threadGame = nullptr;
	_game = nullptr;
	packager = _packager;
	graphicEngine = new GraphicEngine(packager);
	mainmenu = new MainMenu(graphicEngine, net);
	this->net = net;
	Callback_t fptr = [this](void *) {this->launchObserver(); return nullptr; };
	launchLoop = new TaskScheduler(fptr, 50);

	graphicEngine->createWindow(1024, 768, "R-Type");
	graphicEngine->launch();
	cond = 1;
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

		int width = getGraphicEngine()->getWindowWidth();
		int height = getGraphicEngine()->getWindowHeight();
		_game = new class Game(width, height, images, _nickname, packager);

		inGame = true;
		graphicEngine->setMouseClickCallback(nullptr);	// In game, don't bother to call MainMenu::OnClick
		graphicEngine->setMouseMovedCallback(nullptr);
		usableKeyPressedCallback ptr = std::bind(&Game::handlePlayerMovement, _game, std::placeholders::_1);
		graphicEngine->setUsableKeyPressedCallback(ptr);
		threadGame = new Thread([&](void *) -> void * {
			while (cond) {
				if (mainmenu != nullptr) {
					delete mainmenu;
					mainmenu = nullptr;
				}
				_game->run();
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
	/*static Sprite *bg = nullptr;

	if (!bg) {
		Transformation t;
		t.setBounds(1024, 768);
		t.setPosition(0, 0);
		bg = new Sprite("menubackground8bit.png", t, graphicEngine, Color::None);
	}
	bg->draw();*/

  images.for_each([&](auto &img) {
    this->graphicEngine->drawSprite(*img);
    delete img;
  });
  _nickname.for_each([&](auto &text) {
    this->graphicEngine->drawText(*text);
    delete text;
  });

	_nickname.clear();
	images.clear();
}
