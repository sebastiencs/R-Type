#include "OnlineMenu.hh"
#include "IOEvent.hh"
#include "Cell.hh"

OnlineMenu::OnlineMenu(IGraphicEngine* eng)
{
	engine = eng;
	Transformation t(350, 150);
	t.setBounds(300, 250);
	scrollView = new ScrollView(t, 9, engine);
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

	scrollView->emptyCell();
	// TODO: Revoir cette boucle. C'est moche
	//       Faudrait uniquement envoyer le paquet dans cette fonction
	//       et gerer la reception du paquet de reponse autre part
	const Paquet	*tmp;
	int loop = 0;
	do {
		tmp = PS.getGameListPackage();
	} while (!tmp && !IOEvent::wait(150) && ++loop < 10);

	if (tmp) {
		PaquetListParties paquetList((void *)tmp->getData(), tmp->getSize());

		scrollView->emptyCell();
		for (auto &party : paquetList.getParties()) {
			scrollView->createCell(std::get<0>(party), std::get<1>(party));
		}
		PS.deleteGameListPackage();
	}
}

void OnlineMenu::draw()
{
	onlineChoiseBox->draw();
	scrollView->draw();
	if (createGameMenu != nullptr)
		createGameMenu->draw();
}

void OnlineMenu::onClick(uint32_t x, uint32_t y)
{
	if (onlineChoiseBox->isPressed(x, y))
		onlineChoiseBox->onAction();

	else if (createGameMenu != nullptr) {
		createGameMenu->onClick(x, y);
	}
	else if (scrollView->isPressed(x, y))
		scrollView->onAction();
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
	for (Cell *c : scrollView->getListCell())
		if (c->getId() == scrollView->getSelectCell())
			Packager::createJoinPartyPackage(c->getNameParty());
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
