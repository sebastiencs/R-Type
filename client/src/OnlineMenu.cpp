#include "OnlineMenu.hh"
#include "IThread.hh"
#include "Timer.hh"
#include "ListPlayers.hh"

OnlineMenu::OnlineMenu(IGraphicEngine_SharedPtr eng)
  : engine(std::move(eng))
{
	Transformation t(350, 150);
	t.setBounds(300, 250);
	scrollView = new ScrollView(t, 9, engine);
	createGameMenu = nullptr;
	threadReceivedParties = nullptr;
	lobby = nullptr;
	inLobby = false;
	partyListUpdate = false;
	menu();
}

OnlineMenu::~OnlineMenu()
{
	if (scrollView)
		delete(scrollView);

	if (threadReceivedParties) {
		threadReceivedParties->close();
		delete threadReceivedParties;
		threadReceivedParties = nullptr;
	}
}

void OnlineMenu::createRequestPartiesPaquet()
{
	Packager::createGameListPackage();
	if (threadReceivedParties && threadReceivedParties->isRunning()) {
		DEBUG_MSG("Thread was already running, resetting it");
		games.clear();
		threadReceivedParties->close();
		threadReceivedParties->reRun();
		return;
	}
	else if (threadReceivedParties) {
		games.clear();
		threadReceivedParties->reRun();
		return;
	}
	Callback_t fptr = [this](void* param) {
		std::list<PartyNB>* list = reinterpret_cast<std::list<PartyNB>*>(param);
		PackageStorage &PS = PackageStorage::getInstance();
		const PaquetListParties	*tmp = nullptr;
		while (!tmp) {
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			if ((tmp = PS.getGameListPackage())) {
				for (auto &party : tmp->getParties()) {
					list->push_back(party);
				}
				PS.deleteGameListPackage();
				DEBUG_MSG("Request received");
				this->setPartyListUpdate(true);
			}
		}
		return list;
	};
	if (!threadReceivedParties) {
		games.clear();
		threadReceivedParties = new Thread(fptr, &games);
		DEBUG_MSG("Request sent");
	}
}

void OnlineMenu::setPartyListUpdate(bool changed)
{
	partyListUpdate = changed;
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
		if ((!threadReceivedParties || !threadReceivedParties->isRunning()) && partyListUpdate) {
			scrollView->emptyCell();
			for (PartyNB p : games)
				scrollView->createCell(std::get<0>(p), std::get<1>(p));
			games.clear();
			partyListUpdate = false;
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
		if (createGameMenu != nullptr) {
			if (createGameMenu->onClick(x, y))
				return true;
		}
		if (onlineChoiseBox->onAction(x, y))
			return true;
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
	PackageStorage &PS = PackageStorage::getInstance();
	for (auto &c : scrollView->getListCell())
		if (c->getId() == scrollView->getSelectCell()) {
			Packager::createJoinPartyPackage(static_cast<Cell*>(c.get())->getNameParty());

			const PaquetResponse *paquet = nullptr;
			ITimer *t = new Timer();
			t->start();
			do { paquet = PS.getAnswersPackage(); } while (!paquet && t->ms() < 3000);
			delete t;
			if (paquet && paquet->getReturn() == 3) {
				DEBUG_MSG("Can't join party");
				PS.deleteAnswersPackage();
				return;
			}
			PS.deleteAnswersPackage();

			inLobby = true;

			if (lobby == nullptr) {
				if (threadReceivedParties) {
					threadReceivedParties->close();
					delete threadReceivedParties;
					threadReceivedParties = nullptr;
				}

				/* a changer? on att que le serv nous renvoie la liste des joueurs avant de rejoindre (= freeze)*/
				ListPlayers &LP = ListPlayers::getInstance();
				const PaquetListPlayers	*paquetList = nullptr;

				ITimer* t = new Timer();
				t->start();
				while (!paquetList && t->ms() < 3000) {
					if ((paquetList = PS.getPlayerListPackage())) {
						for (auto p : paquetList->getPlayers()) {
							if (LP.getPlayer(std::get<1>(p)) == nullptr)
							  LP.addPlayer(std::make_shared<Player>(std::get<0>(p), std::get<1>(p), std::get<2>(p)));
						}
						PS.deletePlayerListPackage();
					}
				}
				delete t;
				/* ! */
				lobby = std::make_shared<LobbyMenu>(engine, this);
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
	list.clearList();
	lobby.reset();
	inLobby = false;
	createRequestPartiesPaquet();
	DEBUG_MSG("You just left the lobby");
}

void OnlineMenu::onCreateGame()
{
	Packager::createCreatePartyPackage(createGameMenu->getServerName()->getText());
	PackageStorage &PS = PackageStorage::getInstance();

	delete createGameMenu;
	createGameMenu = nullptr;

	const PaquetResponse *paquet = nullptr;
	ITimer *t = new Timer();
	t->start();
	do { paquet = PS.getAnswersPackage(); } while (!paquet && t->ms() < 3000);
	delete t;

	if (!paquet) {
	  std::cerr << "Answer not received" << std::endl;
	}
	if (paquet && paquet->getReturn() == 3) {
		DEBUG_MSG("Can't create party");
		PS.deleteAnswersPackage();
		return;
	}
	else if (paquet) {
	  PS.deleteAnswersPackage();
	}

	inLobby = true;
	if (lobby == nullptr) {
		if (threadReceivedParties) {
			threadReceivedParties->close();
			delete threadReceivedParties;
			threadReceivedParties = nullptr;
		}
		lobby = std::make_shared<LobbyMenu>(engine, this);
	}
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
	onlineChoiseBox->addDrawable(std::make_shared<Button>("Refresh", "refreshButton.png", transformation, Color::None, fptr, "Refresh", engine));

	fptr = std::bind(&OnlineMenu::joinButton, this);
	onlineChoiseBox->addDrawable(std::make_shared<Button>("Join", "joinButton.png", transformation, Color::None, fptr, "Join", engine));

	fptr = std::bind(&OnlineMenu::createButton, this);
	onlineChoiseBox->addDrawable(std::make_shared<Button>("Info", "infoButton.png", transformation, Color::None, fptr, "Info", engine));
}
