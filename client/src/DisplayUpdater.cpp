#include "DisplayUpdater.hh"
#include "SystemAudio.hh"
#include "Game.hh"

DisplayUpdater::DisplayUpdater(Packager * _packager, NetworkClient *net) : inGame(false)
{
	threadGame = nullptr;
	mutex = nullptr;
	_game = nullptr;
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
	if (threadGame)
		delete threadGame;
	if (mutex)
		delete mutex;
	mutex = nullptr;
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

		mutex = new Mutex();

		int width = getGraphicEngine()->getWindowWidth();
		int height = getGraphicEngine()->getWindowHeight();
		_game = new class Game(width, height, images, mutex, _nickname, packager);

		inGame = true;
		graphicEngine->setMouseClickCallback(nullptr);	// In game, don't bother to call MainMenu::OnClick
		graphicEngine->setMouseMovedCallback(nullptr);
		usableKeyPressedCallback ptr = std::bind(&Game::handlePlayerMovement, _game, std::placeholders::_1);
		graphicEngine->setUsableKeyPressedCallback(ptr);
		threadGame = new Thread([this](void *) -> void * {
			for (;;) {
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
	static Sprite *bg = nullptr;

	if (!bg) {
		Transformation t;
		t.setBounds(1024, 768);
		t.setPosition(0, 0);
		bg = new Sprite("menubackground8bit.png", t, graphicEngine, Color::None);
	}
	bg->draw();

	if (mutex) {
		mutex->lock();
		for (Sprite *img : images) {
			graphicEngine->drawSprite(*img);
			delete img;
		}
		for (Text *text : _nickname) {
			graphicEngine->drawText(*text);
			delete text;
		}
		_nickname.clear();
		images.clear();
		mutex->unlock();
	}
}
