#include "OnlineMenu.hh"
#include "IThread.hh"
#include "Timer.hh"
#include "ListPlayers.hh"

OnlineMenu::OnlineMenu(IGraphicEngine_SharedPtr eng)
  : engine(std::move(eng)), cond(1)
{
	Transformation t(350, 150);
	t.setBounds(300, 250);
	scrollView = std::make_shared<ScrollView>(t, 9, engine);
	createGameMenu = nullptr;
	threadReceivedParties = nullptr;
	lobby = nullptr;
	inLobby = false;
	partyListUpdate = false;
	menu();
}

OnlineMenu::~OnlineMenu()
{
  std::cerr << "ONLINE MENU DESTRUCTED" << std::endl;
	if (threadReceivedParties) {
		cond = 0;
		threadReceivedParties->join();
	}
}

void OnlineMenu::createRequestPartiesPaquet()
{
	Packager::createGameListPackage();
	if (threadReceivedParties && threadReceivedParties->isRunning()) {
		DEBUG_MSG("Thread was already running, resetting it");
		games.clear();
		cond = 0;
		threadReceivedParties->join();
		cond = 1;
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
		PaquetListParties_SharedPtr	tmp = nullptr;
		while (!tmp && this->cond) {
			IOEvent::wait(50);
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
		cond = 1;
		threadReceivedParties = std::make_shared<Thread>(fptr, &games);
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

			PaquetResponse_SharedPtr paquet = nullptr;
			ITimer_SharedPtr t = std::make_shared<Timer>();
			t->start();
			do { paquet = PS.getAnswersPackage(); } while (!paquet && t->ms() < 3000);
			if (paquet && paquet->getReturn() == 3) {
				DEBUG_MSG("Can't join party");
				PS.deleteAnswersPackage();
				return;
			}
			PS.deleteAnswersPackage();

			inLobby = true;

			if (lobby == nullptr) {
				if (threadReceivedParties) {
					cond = 0;
					threadReceivedParties->join();
					threadReceivedParties.reset();
				}

				/* a changer? on att que le serv nous renvoie la liste des joueurs avant de rejoindre (= freeze)*/
				ListPlayers &LP = ListPlayers::getInstance();
				PaquetListPlayers_SharedPtr	paquetList = nullptr;

				ITimer_SharedPtr t = std::make_shared<Timer>();
				t->start();
				while (!paquetList && t->ms() < 3000) {
					if ((paquetList = PS.getPlayerListPackage())) {
						for (auto &p : paquetList->getPlayers()) {
							if (LP.getPlayer(std::get<1>(p)) == nullptr)
							  LP.addPlayer(std::make_shared<Player>(std::get<0>(p), std::get<1>(p), std::get<2>(p)));
						}
						PS.deletePlayerListPackage();
					}
				}
				/* ! */
				lobby = std::make_shared<LobbyMenu>(engine, shared_from_this());
				return;
			}
		}
}

void OnlineMenu::backButtonGameMenu()
{
	createGameMenu.reset();
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

	createGameMenu.reset();

	PaquetResponse_SharedPtr paquet = nullptr;
	ITimer_SharedPtr t = std::make_shared<Timer>();
	t->start();
	do { paquet = PS.getAnswersPackage(); } while (!paquet && t->ms() < 3000);

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
			cond = 0;
			threadReceivedParties->join();
			threadReceivedParties = nullptr;
		}
		lobby = std::make_shared<LobbyMenu>(engine, shared_from_this());
	}
}

void OnlineMenu::createButton()
{
	if (createGameMenu == nullptr)
		createGameMenu = std::make_shared<CreateGameMenu>(engine, shared_from_this());
}

void OnlineMenu::menu()
{
	std::function<void()> fptr;
	Transformation transformation(350, 525);
	transformation.setScale(0.8f, 0.8f);

	onlineChoiseBox = std::make_shared<Box>(Orientation::horizontal, transformation, "onlineBox");
	onlineChoiseBox->setSpacing(25);
	fptr = std::bind(&OnlineMenu::createRequestPartiesPaquet, this);
	onlineChoiseBox->addDrawable(std::make_shared<Button>("Refresh", "refreshButton.png", transformation, Color::None, fptr, "Refresh", engine));

	fptr = std::bind(&OnlineMenu::joinButton, this);
	onlineChoiseBox->addDrawable(std::make_shared<Button>("Join", "joinButton.png", transformation, Color::None, fptr, "Join", engine));

	fptr = std::bind(&OnlineMenu::createButton, this);
	onlineChoiseBox->addDrawable(std::make_shared<Button>("Info", "infoButton.png", transformation, Color::None, fptr, "Info", engine));
}
