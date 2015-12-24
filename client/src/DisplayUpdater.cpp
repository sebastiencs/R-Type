#include "DisplayUpdater.hh"
#include "SystemAudio.hh"
#include "Game.hh"
#include "Locker.hh"

DisplayUpdater::DisplayUpdater(Packager_SharedPtr _packager, NetworkClient_SharedPtr _net)
  : packager(std::move(_packager)), net(std::move(_net)), inGame(false), cond(1), dead(false)
{
	threadGame = nullptr;
	_game = nullptr;
	deathTimer = nullptr;
	graphicEngine = std::make_shared<GraphicEngine>();
	mainmenu = std::make_shared<MainMenu>(graphicEngine, net);
	Callback_t fptr = [this](void *) {this->launchObserver(); return nullptr; };
	launchLoop = std::make_shared<TaskScheduler>(fptr, 50);

	xBg1 = 0;
	tBg1.setPosition(xBg1, 0);
	xBg2 = 1920;
	tBg2.setPosition(xBg2, 0);
	bg1 = std::make_shared<Sprite>("ingamebg.png", tBg1, std::move(graphicEngine));
	bg2 = std::make_shared<Sprite>("ingamebg.png", tBg2, std::move(graphicEngine));
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
  }
  if (launchLoop) {
    launchLoop->stop();
  }
}

IGraphicEngine_SharedPtr DisplayUpdater::getGraphicEngine()
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

		ListPlayers &instance = ListPlayers::getInstance();

		auto &list = const_cast<ListSecure<Player_SharedPtr>&>(instance.getListPlayers());

		uint8_t myID = instance.getId();
		uint8_t me = 1;

		for (auto &p : list) {
		  if (p->getID() < myID) {
		    me += 1;
		  }
		}
		// list.sort([] (auto &p1, auto &p2) -> bool { return (p1->getID() < p2->getID()); });

		// uint8_t i = 1;
		// for (auto &p : instance.getListPlayers()) {
		//   if (p->getID() == instance.getId()) {
		//     me = i;
		//   }
		//   i += 1;
		// }
		auto &&player = instance.getPlayer(instance.getId());
		player->setY(100 + 100 * me);

		Packager::createFirstUDPPackage(ListPlayers::getInstance().getId());
		Packager::createFirstUDPPackage(ListPlayers::getInstance().getId());

		int width = getGraphicEngine()->getWindowWidth();
		int height = getGraphicEngine()->getWindowHeight();
		_game = std::make_shared<Game>(width, height, images, _nickname, packager);

		inGame = true;
		graphicEngine->setMouseClickCallback(nullptr);	// In game, don't bother to call MainMenu::OnClick
		graphicEngine->setMouseMovedCallback(nullptr);
		usableKeyPressedCallback ptr = std::bind(&Game::handlePlayerMovement, _game, std::placeholders::_1);
		graphicEngine->setUsableKeyPressedCallback(ptr);
		threadGame = std::make_shared<Thread>([&](void *) -> void * {
			mainmenu.reset();
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
		launchLoop->stop();
	}
}

void DisplayUpdater::game()
{
	xBg1 -= static_cast<uint32_t>((200 * GraphicEngine::getDeltaTimeS()));
	xBg1 = xBg1 < -1920 ? 1920 : xBg1;

	tBg1.setPosition(xBg1, 0);
	bg1->setTransformation(tBg1);
	bg1->draw();
	xBg2 -= static_cast<uint32_t>((200 * GraphicEngine::getDeltaTimeS()));

	xBg2 = xBg2 < -1920 ? 1920 : xBg2;
	tBg2.setPosition(xBg2, 0);
	bg2->setTransformation(tBg2);
	bg2->draw();


  images.for_each([&](auto &img) {
    this->graphicEngine->drawSprite(*img);
  });
  _nickname.for_each([&](auto &text) {
    this->graphicEngine->drawText(*text);
  });

	if (dead) {
		if (deathTimer) {
			Transformation t = Transformation((graphicEngine->getWindowWidth() / 2) - 80, (graphicEngine->getWindowHeight() / 2) - 50);
			Text text = Text("YOU DIED", DEFAULT_FONT, 30, t, std::move(graphicEngine), Color(150, 0, 0));
			if (deathTimer->ms() < 7000) {
				graphicEngine->drawText(text);
			}
			else {
				deathTimer = nullptr;
				dead = false;
				threadGame->close();
				graphicEngine->setUsableKeyPressedCallback(nullptr);
				_game = nullptr;
				graphicEngine->closeWindow();
			}
		}
		else {
			deathTimer = std::make_shared<Timer>();
			deathTimer->start();
		}
	}

	_nickname.clear();
	images.clear();
}
