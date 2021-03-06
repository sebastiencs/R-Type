#include "LobbyMenu.hh"
#include "ListPlayers.hh"
#include "SystemAudio.hh"
#include "Chat.hh"
#include "OnlineMenu.hh"

LobbyMenu::LobbyMenu(IGraphicEngine_SharedPtr eng, OnlineMenu_WeakPtr superview)
  : engine(std::move(eng)), _superview(std::move(superview)), cond(1)
{
	right = nullptr;
	threadReceivedListPlayers = nullptr;
	playerListChanged = true;
	Packager::createPlayerListPackage();
	left = std::make_shared<Box>(Orientation::vertical, Transformation(210, 200), "leftBox");
	left->setSpacing(80);
	quadPlayerBox = std::make_shared<Box>(Orientation::vertical, Transformation(0, 0), "quadPlayerBox");
	quadPlayerBox->setSpacing(80);

	createRequestListPlayersPaquet();

	left->addDrawable(quadPlayerBox);
	commands = std::make_shared<Box>(Orientation::horizontal, Transformation(200, 500), "commandBox");
	commands->setSpacing(100);
	callback fptr;
	fptr = std::bind(&LobbyMenu::ready, this);
	readyb = std::make_shared<Button>("Ready", "readyButton.png", Transformation(0, 0), Color::None, fptr, "readyButton", engine);
	unReadyb = std::make_shared<Button>("Unready", "unreadyButton.png", Transformation(0, 0), Color::None, fptr, "unreadyButton", engine);

	fptr = std::bind(&OnlineMenu::backButtonLobbyMenu, _superview.lock().get());
	commands->addDrawable(std::make_shared<Button>("Leave", "leaveButton.png", Transformation(0, 0), Color::None, fptr, "leaveButton", engine));
	commands->addDrawable(unReadyb);
	left->addDrawable(commands);

	chat = std::make_unique<Chat>(Transformation(750, 200), engine, ListPlayers::getInstance());

        DEBUG_MSG("LobbyMenu created");
}

LobbyMenu::~LobbyMenu()
{
  DEBUG_MSG("LobbyMenu deleted");
	if (threadReceivedListPlayers) {
		cond = 0;
		threadReceivedListPlayers->join();
	}
}

void LobbyMenu::createRequestListPlayersPaquet()
{
	if (threadReceivedListPlayers && threadReceivedListPlayers->isRunning()) {
		DEBUG_MSG("Thread was already running, resetting it");
		cond = 0;
		threadReceivedListPlayers->join();
		cond = 1;
		threadReceivedListPlayers->reRun();
		return;
	}
	else if (threadReceivedListPlayers) {
		threadReceivedListPlayers->reRun();
		return;
	}

	Callback_t fptr = [this](void *cond) {
		PackageStorage &PS = PackageStorage::getInstance();
		ISystemAudio &audio = SystemAudio::getInstance();
		ListPlayers &LP = ListPlayers::getInstance();

		PaquetListPlayers_SharedPtr	tmp = nullptr;
		PaquetReady_SharedPtr	tmp2 = nullptr;
		int *c = reinterpret_cast<int *>(cond);

		while (*c && !tmp && !tmp2) {
			IOEvent::wait(50);
			if ((tmp = PS.getPlayerListPackage())) {
				LP.clearList();
				for (auto p : tmp->getPlayers()) {
				  if (LP.getPlayer(std::get<1>(p)) == nullptr) {
				    LP.addPlayer(std::make_shared<Player>(std::get<0>(p), std::get<1>(p), std::get<2>(p)));
				    audio.playSound(ISystemAudio::JOIN);
				  }
				}
				PS.deletePlayerListPackage();
				DEBUG_MSG("Request received");
				this->setPlayerListChanged(true);
			}

			if ((tmp2 = PS.getReadyPackage())) {
				for (auto &p : LP.getListPlayers()) {
				  if (p->getID() == tmp2->getID()) {
				    p->setReady((tmp2->getStatus()) ? (1) : (0));
				  }
				}
				PS.deleteReadyPackage();
				DEBUG_MSG("Request received");
				this->setPlayerListChanged(true);
			}
		}

		return nullptr;
	};

	if (!threadReceivedListPlayers) {
		threadReceivedListPlayers = std::make_shared<Thread>(fptr, &cond);
		DEBUG_MSG("Request sent");
	}
}

void LobbyMenu::draw()
{
	if (playerListChanged)
		updatePlayerList();
	if (left)
		left->draw();
	if (right)
		right->draw();
	if (chat)
		chat->draw();
}

void LobbyMenu::onHover(const uint32_t x, const uint32_t y)
{
	left->onHover(x, y);
}

bool LobbyMenu::onClick(const uint32_t x, const uint32_t y)
{
	if (left->onAction(x, y))
		return true;
	return false;
}

void LobbyMenu::setPlayerListChanged(const bool changed)
{
	playerListChanged = changed;
}

void LobbyMenu::ready()
{
	ListPlayers &list = ListPlayers::getInstance();
	Box_SharedPtr players = std::dynamic_pointer_cast<Box>(left->getElement("quadPlayerBox"));
	if (!players) {
		DEBUG_MSG("Couldn't retreive QuadPlayerBox");
		return;
	}
	Box_SharedPtr player = std::dynamic_pointer_cast<Box>(players->getElement("Player" + std::to_string(list.getId()) + "Box"));
	if (!player) {
		DEBUG_MSG("Couldn't retreive Player Box: \"" << "Player" << std::to_string(list.getId()) << "Box" << "\"");
		return;
	}
	TextField_SharedPtr ready = std::dynamic_pointer_cast<TextField>(player->getElement("Ready"));
	if (!ready)
		return;
	if (ready->getText() == "Ready") {
		ready->setText("Unready");
		ready->setColor(Color::Red);
		commands->removeDrawable(readyb);
		commands->addDrawable(unReadyb);
		list.getPlayer(list.getId())->setReady(0);
		Packager::createReadyPackage(list.getId(), 0);
	}
	else {
		ready->setText("Ready");
		ready->setColor(Color::Green);
		commands->removeDrawable(unReadyb);
		commands->addDrawable(readyb);
		list.getPlayer(list.getId())->setReady(1);
		Packager::createReadyPackage(list.getId(), 1);
	}
}

void LobbyMenu::updatePlayerList()
{
	quadPlayerBox->clearElements();
	const ListPlayers& playerList = ListPlayers::getInstance();
	std::string ready = "Unready";
	Color cReady = Color::Red;
	size_t t = 0;
	for (auto &p : playerList.getListPlayers()) {
		Transformation tr(0, 0);
		tr.setScale(0.5f, 0.5f);
		Sprite_SharedPtr playerVessel = std::make_shared<Sprite>("vessel" + std::to_string(t) + ".png", tr, std::move(engine));
		tr.setScale(1.0f, 1.0f);
		TextField_SharedPtr playerName = std::make_shared<TextField>(p->getName(), tr, DEFAULT_FONT_SIZE + 10, DEFAULT_FONT, Color::White, p->getName(), engine);
		TextField_SharedPtr playerLVL = std::make_shared<TextField>("0", tr, DEFAULT_FONT_SIZE + 10, DEFAULT_FONT, Color::White, "LVL", engine);
		if (p->getReady()) {
			ready = "Ready";
			cReady = Color::Green;
		}
		else {
			ready = "Unready";
			cReady = Color::Red;
		}
		TextField_SharedPtr playerStatus = std::make_shared<TextField>(ready, tr, DEFAULT_FONT_SIZE + 10, DEFAULT_FONT, cReady, "Ready", engine);
		Box_SharedPtr box = std::make_shared<Box>(Orientation::horizontal, Transformation(200, 200), "Player" + std::to_string(p->getID()) + "Box");
		box->setSpacing(50);
		box->addDrawable(playerVessel);
		box->addDrawable(playerName);
#ifdef DEBUG
		TextField_SharedPtr playerID = std::make_shared<TextField>("ID: " + std::to_string(p->getID()), tr, DEFAULT_FONT_SIZE + 10, DEFAULT_FONT, Color::White, p->getName(), engine);
		box->addDrawable(playerID);
#endif // !DEBUG
		box->addDrawable(playerLVL);
		box->addDrawable(playerStatus);
		quadPlayerBox->addDrawable(box);
		++t;
	}
	while (t < 4) {
		TextField_SharedPtr empty = std::make_shared<TextField>("EMPTY", Transformation(0, 0), DEFAULT_FONT_SIZE + 10, DEFAULT_FONT, Color::White, "EMPTY", engine);
		quadPlayerBox->addDrawable(empty);
		++t;
	}
	threadReceivedListPlayers->reRun();
	playerListChanged = false;
}
