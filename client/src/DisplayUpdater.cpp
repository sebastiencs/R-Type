#include "DisplayUpdater.hh"
#include "SystemAudio.hh"
#include "Game.hh"

DisplayUpdater::DisplayUpdater(Packager * _packager, NetworkClient *net)
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
	delete threadGame;
	delete mutex;
	mutex = nullptr;
	delete _game;
	//	delete graphicEngine;   // Problem de thread. Je comprends pas l'erreur. Seb
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
	static PackageStorage& ps = PackageStorage::getInstance();
	auto launch = ps.getLaunchPackage();

	if (launch != nullptr) {

		mutex = new Mutex();

		int width = getGraphicEngine()->getWindowWidth();
		int height = getGraphicEngine()->getWindowHeight();
		_game = new class Game(width, height, images, mutex, pseudo);

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

#include "AnimatedSprite.hh"

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
		for (auto &img : images) {
//			if (img.img == "bullets-8.png") {
//				AnimatedSprite *test = new AnimatedSprite(img.img, 30, img.t, graphicEngine);
//				test->draw();
//			}
//			else
				graphicEngine->drawImage(img.img, img.t);
		}
		for (auto &text : pseudo) {
			graphicEngine->drawText(text.img, text.t, 12);
		}
		pseudo.clear();
		images.clear();
		mutex->unlock();
	}
}
