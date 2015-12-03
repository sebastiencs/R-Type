#include "OnlineMenu.hh"

OnlineMenu::OnlineMenu(IGraphicEngine* eng)
{
	engine = eng;
	Transformation t(350, 150);
	t.setBounds(300, 250);
	scrollView = new ScrollView(t, 9, engine);
	lobby = new LobbyMenu(engine);
	createGameMenu = nullptr;
	menu();
}

OnlineMenu::~OnlineMenu()
{
	delete(scrollView);
}

void OnlineMenu::createRequestPartiesPaquet()
{
	PackageStorage &PS = PackageStorage::getInstance();

	PaquetRequestParties	*paquet = new PaquetRequestParties();
	paquet->createPaquet();
	PS.storeToSendTCPPackage(paquet);
	DEBUG_MSG("Request send");
}

void OnlineMenu::draw()
{
	PackageStorage &PS = PackageStorage::getInstance();
	const Paquet	*tmp;

	if (tmp = PS.getGameListPackage()) {
		PaquetListParties paquetList((void *)tmp->getData(), tmp->getSize());

		scrollView->emptyCell();
		for (auto &party : paquetList.getParties()) {
			scrollView->createCell(std::get<0>(party), std::get<1>(party));
		}
		PS.deleteGameListPackage();
		DEBUG_MSG("Request received");
	}
	onlineChoiseBox->draw();
	scrollView->draw();
	if (createGameMenu != nullptr)
		createGameMenu->draw();

}

bool OnlineMenu::onClick(uint32_t x, uint32_t y)
{
	if (onlineChoiseBox->onAction(x, y))
		return true;
	else if (createGameMenu != nullptr) {
		if (createGameMenu->onClick(x, y))
			return true;
	}
	if (scrollView->onAction(x, y)) {
		return true;
	}
	return false;
}

void OnlineMenu::onHover(uint32_t x, uint32_t y)
{
	onlineChoiseBox->onHover(x, y);
	scrollView->onHover(x, y);
	if (createGameMenu != nullptr) {
		createGameMenu->onHover(x, y);
	}
}

void OnlineMenu::joinButton()
{
	for (Drawable *c : scrollView->getListCell())
		if (c->getId() == scrollView->getSelectCell())
			Packager::createJoinPartyPackage(static_cast<Cell *>(c)->getNameParty());
}

void OnlineMenu::backButton()
{
	delete createGameMenu;
	createGameMenu = nullptr;
}

void OnlineMenu::onCreateGame()
{
	PackageStorage &PS = PackageStorage::getInstance();

	PaquetCreateParty	*paquet = new PaquetCreateParty();

	paquet->setName(createGameMenu->getServerName()->getText());
	paquet->createPaquet();
	DEBUG_MSG("Create party : " + createGameMenu->getServerName()->getText());
	PS.storeToSendTCPPackage(paquet);
	delete createGameMenu;
	createGameMenu = nullptr;
	createRequestPartiesPaquet();
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
