#include "LobbyMenu.hh"
#include "ListPlayers.hh"

LobbyMenu::LobbyMenu(IGraphicEngine* engine, OnlineMenu *superview) : engine(engine)
{
	_superview = superview;
	right = nullptr;
	threadReceivedListPlayers = nullptr;
	playerListChanged = true;
	Packager::createPlayerListPackage();
	left = new Box(Orientation::vertical, Transformation(250, 200), "leftBox");
	left->setSpacing(80);
	quadPlayerBox = new Box(Orientation::vertical, Transformation(0, 0), "quadPlayerBox");
	quadPlayerBox->setSpacing(80);

	createRequestListPlayersPaquet();

	left->addDrawable(quadPlayerBox);
	commands = new Box(Orientation::horizontal, Transformation(200, 500), "commandBox");
	commands->setSpacing(100);
	callback fptr;
	fptr = std::bind(&LobbyMenu::ready, this);
	readyb = new Button("Ready", "readyButton.png", Transformation(0, 0), Color::None, fptr, "readyButton", engine);
	unReadyb = new Button("Unready", "unreadyButton.png", Transformation(0, 0), Color::None, fptr, "unreadyButton", engine);

	fptr = std::bind(&OnlineMenu::backButtonLobbyMenu, _superview);
	commands->addDrawable(new Button("Leave", "leaveButton.png", Transformation(0, 0), Color::None, fptr, "leaveButton", engine));
	commands->addDrawable(unReadyb);
	left->addDrawable(commands);
}

LobbyMenu::~LobbyMenu()
{
	if (threadReceivedListPlayers) {
		threadReceivedListPlayers->close();
		delete threadReceivedListPlayers;
	}
	if (left)
		delete left;
	if (commands)
		delete commands;
	if (right)
		delete right;
}

void LobbyMenu::createRequestListPlayersPaquet()
{
	if (threadReceivedListPlayers && threadReceivedListPlayers->isRunning()) {
		DEBUG_MSG("Thread was already running, resetting it");
		threadReceivedListPlayers->close();
		threadReceivedListPlayers->reRun();
		return;
	}
	else if (threadReceivedListPlayers) {
		threadReceivedListPlayers->reRun();
		return;
	}

	Callback_t fptr = [this](void *) {
		PackageStorage &PS = PackageStorage::getInstance();
		ListPlayers &LP = ListPlayers::getInstance();

		const PaquetListPlayers	*tmp = nullptr;
		const PaquetReady	*tmp2 = nullptr;

		while (!tmp && !tmp2) {
			IOEvent::wait(50);
			if ((tmp = PS.getPlayerListPackage())) {
				LP.clearList();
				for (auto p : tmp->getPlayers()) {
					if (LP.getPlayer(std::get<1>(p)) == nullptr)
						LP.addPlayer(new Player(std::get<0>(p), std::get<1>(p), std::get<2>(p)));
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
		threadReceivedListPlayers = new Thread(fptr, nullptr);
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
}

void LobbyMenu::onHover(uint32_t x, uint32_t y)
{
	left->onHover(x, y);
//	right->onHover(x, y);
}

bool LobbyMenu::onClick(uint32_t x, uint32_t y)
{
	if (left->onAction(x, y))
		return true;
	//if (right->onAction(x, y)
	//	return true;
	return false;
}

void LobbyMenu::setPlayerListChanged(bool changed)
{
	playerListChanged = changed;
}

void LobbyMenu::ready()
{
	ListPlayers &list = ListPlayers::getInstance();
	Box* players = dynamic_cast<Box* >(left->getElement("quadPlayerBox"));
	if (!players) {
		DEBUG_MSG("Couldn't retreive QuadPlayerBox");
		return;
	}
	Box* player = dynamic_cast<Box* >(players->getElement("Player" + std::to_string(list.getId()) + "Box"));
	if (!player) {
		DEBUG_MSG("Couldn't retreive Player Box: \"" << "Player" << std::to_string(list.getId()) << "Box" << "\"");
		return;
	}
	TextField* ready = dynamic_cast<TextField*>(player->getElement("Ready"));
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
	ListPlayers& playerList = ListPlayers::getInstance();
	std::string ready = "Unready";
	Color cReady = Color::Red;
	size_t t = 0;
	for (Player* p : playerList.getListPlayers()) {
		Transformation tr(0, 0);
		tr.setScale((float)2.0, (float)2.0);
		Sprite* playerVessel = new Sprite("vessel" + std::to_string(t) + ".png", tr, engine);
		tr.setScale((float)1, (float)1);
		TextField* playerName = new TextField(p->getName(), tr, DEFAULT_FONT_SIZE + 10, DEFAULT_FONT, Color::White, p->getName(), engine);
		TextField* playerLVL = new TextField("0", tr, DEFAULT_FONT_SIZE + 10, DEFAULT_FONT, Color::White, "LVL", engine);
		if (p->getReady()) {
			ready = "Ready";
			cReady = Color::Green;
		}
		else {
			ready = "Unready";
			cReady = Color::Red;
		}
		TextField* playerStatus = new TextField(ready, tr, DEFAULT_FONT_SIZE + 10, DEFAULT_FONT, cReady, "Ready", engine);
		Box* box = new Box(Orientation::horizontal, Transformation(200, 200), "Player" + std::to_string(p->getID()) + "Box");
		box->setSpacing(50);
		box->addDrawable(playerVessel);
		box->addDrawable(playerName);
#ifdef DEBUG
		TextField* playerID = new TextField("ID: " + std::to_string(p->getID()), tr, DEFAULT_FONT_SIZE + 10, DEFAULT_FONT, Color::White, p->getName(), engine);
		box->addDrawable(playerID);
#endif // !DEBUG
		box->addDrawable(playerLVL);
		box->addDrawable(playerStatus);
		quadPlayerBox->addDrawable(box);
		++t;
	}
	while (t < 4) {
		TextField* empty = new TextField("EMPTY", Transformation(0, 0), DEFAULT_FONT_SIZE + 10, DEFAULT_FONT, Color::White, "EMPTY", engine);
		quadPlayerBox->addDrawable(empty);
		++t;
	}
	threadReceivedListPlayers->reRun();
	playerListChanged = false;
}
