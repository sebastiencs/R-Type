#include "OnlineMenu.hh"

OnlineMenu::OnlineMenu(IGraphicEngine* eng)
{
	engine = eng;
	Transformation t(350, 150);
	t.setBounds(300, 250);
	scrollView = new ScrollView(t, 9, engine);
}

OnlineMenu::~OnlineMenu()
{
	delete(scrollView);
}

void OnlineMenu::createRequestPartiesPaquet()
{
	PaquetListParties *list = new PaquetListParties();
	list->addParty("Party 0", 2);
	list->addParty("Party 1", 1);
	list->addParty("Party 2", 4);
	list->addParty("Party 3", 0);
	list->addParty("Party 4", 3);
	list->addParty("Party 5", 2);
	list->addParty("Party 6", 1);
	list->addParty("Party 7", 4);
	list->addParty("Party 8", 0);
	list->addParty("Party 9", 0);
	list->addParty("Party 10", 0);
	list->addParty("Party 11", 0);
	list->addParty("Party 12", 0);
	list->addParty("Party 13", 0);
	scrollView->emptyCell();
	for (PartyNB party : list->getParties()) {
		scrollView->createCell(std::get<0>(party), std::get<1>(party));
	}
	DEBUG_MSG("Create Request Parties Paquet");
}

void OnlineMenu::draw()
{
	for (Button* b : buttons)
		b->draw();
	scrollView->draw();
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
}

void OnlineMenu::onHover(uint32_t x, uint32_t y)
{
	for (Button *b : buttons) {
		b->onHover(x, y);
	}
	scrollView->onHover(x, y);
}

void OnlineMenu::joinButton()
{
	for (Cell *c : scrollView->getListCell())
		if (c->getId() == scrollView->getSelectCell())
		{
			PaquetJoinParty *paquet = new PaquetJoinParty();
			paquet->setName(c->getNameParty());
			std::cout << paquet->getName() << " -> ";
			paquet->createPaquet();
			DEBUG_MSG(paquet);
			PackageStorage::getInstance().storeToSendPackage(paquet);
		}

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
	buttons.push_back(new Button("Info", "Button.png", transformation, Color::None, fptr, "Info", engine));
}