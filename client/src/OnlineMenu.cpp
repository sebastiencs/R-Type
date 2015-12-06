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
		threadReceivedParties = nullptr;
	}
}

void OnlineMenu::createRequestPartiesPaquet()
{
	Callback_t fptr = [](void* param) {
		std::list<PartyNB>* list = reinterpret_cast<std::list<PartyNB>*>(param);
		PackageStorage &PS = PackageStorage::getInstance();
		const Paquet	*tmp = nullptr;
		while (tmp == nullptr) {
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			if ((tmp = PS.getGameListPackage())) {
				PaquetListParties paquetList((void *)tmp->getData(), tmp->getSize());
				for (auto &party : paquetList.getParties()) {
					list->push_back(party);
				}
				PS.deleteGameListPackage();
				DEBUG_MSG("Request received");
			}
		}
		return list;
	};
	Packager::createGameListPackage();
	if (threadReceivedParties && threadReceivedParties->isRunning()) {
		DEBUG_MSG("Thread was already running, resetting it");
		games.clear();
		threadReceivedParties->close();
		threadReceivedParties->run(fptr, &games);
	}
	if (!threadReceivedParties) {
		games.clear();
		threadReceivedParties = new Thread(fptr, &games);
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
		if ((!threadReceivedParties || !threadReceivedParties->isRunning()) && !games.empty()) {
			scrollView->emptyCell();
			for (PartyNB p : games)
				scrollView->createCell(std::get<0>(p), std::get<1>(p));
			games.clear();
		}
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
					threadReceivedParties = nullptr;
				}
				lobby = new LobbyMenu(engine, this);

				/* TMP */
//			PackageStorage &PS = PackageStorage::getInstance();
//			ListPlayers &LP = ListPlayers::getInstance();
//			const Paquet	*tmp = nullptr;
//
//			if ((tmp = PS.getPlayerListPackage())) {
//				PaquetListPlayers paquetList((void *)tmp->getData(), tmp->getSize());
//				for (auto p : paquetList.getPlayers()) {
//					if (LP.getPlayer(std::get<1>(p)) == nullptr)
//						LP.addPlayer(new Player(std::get<0>(p), std::get<1>(p), std::get<2>(p)));
//				}
//				PS.deletePlayerListPackage();
//			}
			/* !TMP */
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
