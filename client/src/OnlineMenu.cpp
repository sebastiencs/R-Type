#include "OnlineMenu.hh"
#include "IThread.hh"
#include "ListPlayers.hh"

OnlineMenu::OnlineMenu(IGraphicEngine* eng)
{
	engine = eng;
	Transformation t(350, 150);
	t.setBounds(300, 250);
	scrollView = new ScrollView(t, 9, engine);
	createGameMenu = nullptr;
	threadReceivedParties = nullptr;
	lobby = nullptr;
	inLobby = false;
	menu();
}

OnlineMenu::~OnlineMenu()
{
	delete(scrollView);

	if (threadReceivedParties) {
		threadReceivedParties->close();
		delete threadReceivedParties;
	}
}

void OnlineMenu::createRequestPartiesPaquet()
{
	Packager::createGameListPackage();
	// TODO: add isRunning to know if thread should be called again
	if (!threadReceivedParties) {
		Callback_t fptr = [this](void *arg) {
			PackageStorage &PS = PackageStorage::getInstance();
			const Paquet	*tmp = nullptr;

			while (tmp == nullptr) {
				if ((tmp = PS.getGameListPackage())) {
					Sleep(3000);
					PaquetListParties paquetList((void *)tmp->getData(), tmp->getSize());

					scrollView->emptyCell();
					for (auto &party : paquetList.getParties()) {
						scrollView->createCell(std::get<0>(party), std::get<1>(party));
					}
					PS.deleteGameListPackage();
					DEBUG_MSG("Request received");
				}
			}
			return nullptr;
		};
		threadReceivedParties = new Thread(fptr, nullptr);
		DEBUG_MSG("Request sent");
	}
}

void OnlineMenu::draw()
{
	if (inLobby && lobby != nullptr)
		lobby->draw();
	else {
		onlineChoiseBox->draw();
		scrollView->draw();
		if (createGameMenu != nullptr)
			createGameMenu->draw();
	}
}

bool OnlineMenu::onClick(uint32_t x, uint32_t y)
{
	if (inLobby && lobby != nullptr) {
		if (lobby->onClick(x, y))
			return (true);
	}
	else {
		if (onlineChoiseBox->onAction(x, y))
			return true;
		else if (createGameMenu != nullptr) {
			if (createGameMenu->onClick(x, y))
				return true;
		}
		if (scrollView->onAction(x, y)) {
			return true;
		}
	}
	return false;
}

void OnlineMenu::onHover(uint32_t x, uint32_t y)
{
	if (inLobby && lobby != nullptr)
		lobby->onHover(x, y);
	else {
		onlineChoiseBox->onHover(x, y);
		scrollView->onHover(x, y);
		if (createGameMenu != nullptr) {
			createGameMenu->onHover(x, y);
		}
	}
}

void OnlineMenu::joinButton()
{
	for (Drawable *c : scrollView->getListCell())
		if (c->getId() == scrollView->getSelectCell()) {
			Packager::createJoinPartyPackage(static_cast<Cell *>(c)->getNameParty());
			
			inLobby = true;
			if (lobby == nullptr) {
				if (threadReceivedParties) {
					threadReceivedParties->close();
					delete threadReceivedParties;
				}
				lobby = new LobbyMenu(engine, this);
				return;
			}
		}
}

void OnlineMenu::backButtonGameMenu()
{
	delete createGameMenu;
	createGameMenu = nullptr;
}

void OnlineMenu::backButtonLobbyMenu()
{
	ListPlayers &list = ListPlayers::getInstance();
	Packager::createLeavePackage(list.getId());

	delete lobby;
	lobby = nullptr;
	inLobby = false;
	DEBUG_MSG("You just left the lobby");
}

void OnlineMenu::onCreateGame()
{
	Packager::createCreatePartyPackage(createGameMenu->getServerName()->getText());
	createRequestPartiesPaquet();

	delete createGameMenu;
	createGameMenu = nullptr;

	inLobby = true;
	if (lobby == nullptr)
		lobby = new LobbyMenu(engine, this);
}

void OnlineMenu::createButton()
{
	if (createGameMenu == nullptr)
		createGameMenu = new CreateGameMenu(engine, this);
}

void OnlineMenu::menu()
{
	std::function<void()> fptr;
	Transformation transformation(350, 525);
	transformation.setScale((float)0.8, (float)0.8);

	onlineChoiseBox = new Box(Orientation::horizontal, transformation, "onlineBox");
	onlineChoiseBox->setSpacing(25);
	fptr = std::bind(&OnlineMenu::createRequestPartiesPaquet, this);
	onlineChoiseBox->addDrawable(new Button("Refresh", "refreshButton.png", transformation, Color::None, fptr, "Refresh", engine));

	fptr = std::bind(&OnlineMenu::joinButton, this);
	onlineChoiseBox->addDrawable(new Button("Join", "joinButton.png", transformation, Color::None, fptr, "Join", engine));

	fptr = std::bind(&OnlineMenu::createButton, this);
	onlineChoiseBox->addDrawable(new Button("Info", "infoButton.png", transformation, Color::None, fptr, "Info", engine));
}
