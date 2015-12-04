#include "LobbyMenu.hh"
#include "ListPlayers.hh"

LobbyMenu::LobbyMenu(IGraphicEngine* engine, OnlineMenu *superview) : engine(engine)
{
	_superview = superview;
	right = nullptr;
	left = new Box(Orientation::vertical, Transformation(250, 200), "leftBox");
	left->setSpacing(80);
	for (size_t t = 0; t < 4; ++t) {
		Transformation tr(0, 0);
		tr.setScale((float)2.0, (float)2.0);
		Sprite* playerVessel = new Sprite("vessel" + std::to_string(t) + ".png", tr, engine);
		tr.setScale((float)1, (float)1);
		TextField* playerName = new TextField("Player" + std::to_string(t), tr, DEFAULT_FONT_SIZE + 10, DEFAULT_FONT, Color::White, "Player" + std::to_string(t), engine);
		TextField* playerLVL = new TextField("0", tr, DEFAULT_FONT_SIZE + 10, DEFAULT_FONT, Color::White, "LVL", engine);
		TextField* playerStatus = new TextField("Unready", tr, DEFAULT_FONT_SIZE + 10, DEFAULT_FONT, Color::Red, "Ready", engine);
		Box* box = new Box(Orientation::horizontal, Transformation(200, 200), "Player" + std::to_string(t) + "Box");
		box->setSpacing(50);
		box->addDrawable(playerVessel);
		box->addDrawable(playerName);
		box->addDrawable(playerLVL);
		box->addDrawable(playerStatus);
		playerInfo.push_back(box);
		left->addDrawable(box);
	}
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
	if (left)
		delete left;
	if (commands)
		delete commands;
	if (right)
		delete right;
}

void LobbyMenu::draw()
{
	if (left)
		left->draw();
	//if (commands)
	//	commands->draw();
	if (right)
		right->draw();
}

void LobbyMenu::onHover(uint32_t x, uint32_t y)
{
	left->onHover(x, y);
//	commands->onHover(x, y);
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

void LobbyMenu::ready()
{
	// TODO: savoir quel # on est, pour l'instant 0
	Box* player = static_cast<Box* >(left->getElement("Player" + std::to_string(0) + "Box"));
	if (!player)
		return;
	TextField* ready = static_cast<TextField*>(player->getElement("Ready"));
	if (!ready)
		return;
	if (ready->getText() == "Ready") {
		ready->setText("Unready");
		ready->setColor(Color::Red);
		commands->removeDrawable(readyb);
		commands->addDrawable(unReadyb);
		ListPlayers &list = ListPlayers::getInstance();
		PaquetReady *ready = new PaquetReady();
		ready->setID(list.getId());
		ready->createPaquet();
		PackageStorage::getInstance().storeToSendTCPPackage(ready);
	}
	else {
		ready->setText("Ready");
		ready->setColor(Color::Green);
		commands->removeDrawable(unReadyb);
		commands->addDrawable(readyb);
		PaquetReady *ready = new PaquetReady();
		ready->setID(ListPlayers::getInstance().getId());
		ready->createPaquet();
		PackageStorage::getInstance().storeToSendTCPPackage(ready);
	}
}
