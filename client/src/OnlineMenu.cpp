#include "OnlineMenu.hh"
#include "IOEvent.hh"

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
	PS.storeToSendPackage(paquet);

	// TODO: Revoir cette boucle. C'est moche
	//       Faudrait uniquement envoyer le paquet dans cette fonction
	//       et gerer la reception du paquet de reponse autre part
	const Paquet	*tmp;
	int loop = 0;
	do {
		tmp = PS.getGameListPackage();
	} while (!tmp && !IOEvent::wait(150) && loop < 10);

	if (tmp) {
		PaquetListParties paquetList((void *)tmp->getData(), tmp->getSize());

		scrollView->emptyCell();
		for (auto &party : paquetList.getParties()) {
			scrollView->createCell(std::get<0>(party), std::get<1>(party));
		}
	}
}

void OnlineMenu::draw()
{
	for (Button* b : buttons)
		b->draw();
	scrollView->draw();
	if (createGameMenu != nullptr)
		createGameMenu->draw();
}

void OnlineMenu::onClick(uint32_t x, uint32_t y)
{
	for (Button *b : buttons) {
		if (b->isPressed(x, y)) {
			b->onAction();
		}
	}
	if (scrollView->isPressed(x, y))
		scrollView->onAction();
	if (createGameMenu != nullptr) {
		createGameMenu->onClick(x, y);
	}
}

void OnlineMenu::onHover(uint32_t x, uint32_t y)
{
	for (Button *b : buttons) {
		b->onHover(x, y);
	}
	scrollView->onHover(x, y);
	if (createGameMenu != nullptr) {
		createGameMenu->onHover(x, y);
	}
}

void OnlineMenu::joinButton()
{
	for (Cell *c : scrollView->getListCell())
		if (c->getId() == scrollView->getSelectCell())
		{
			Packager::createJoinPartyPackage(c->getNameParty());
		}

}

void OnlineMenu::backButton()
{
	delete createGameMenu;
	createGameMenu = nullptr;
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
	transformation.setScale(0.5, 0.5);

	fptr = std::bind(&OnlineMenu::createRequestPartiesPaquet, this);
	buttons.push_back(new Button("Refresh", "refreshButton.png", transformation, Color::None, fptr, "Refresh", engine));

	transformation.setPosition(450, 525);
	fptr = std::bind(&OnlineMenu::joinButton, this);
	buttons.push_back(new Button("Join", "Button.png", transformation, Color::None, fptr, "Join", engine));

	transformation.setPosition(550, 525);
	fptr = std::bind(&OnlineMenu::createButton, this);
	buttons.push_back(new Button("Info", "Button.png", transformation, Color::None, fptr, "Info", engine));
}
