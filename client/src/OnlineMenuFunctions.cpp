#include "OnlineMenuFunctions.hh"

OnlineMenu::OnlineMenu(IGraphicEngine* eng)
{
	engine = eng;
	scrollView = new ScrollView(engine);
}

OnlineMenu::~OnlineMenu()
{
	delete(scrollView);
}

void OnlineMenu::createRequestPartiesPaquet()
{
	PaquetListParties *list = new PaquetListParties();
	list->addParty("First try", 2);
	list->addParty("Second try", 1);
	for (PartyNB party : list->getParties()) {
		scrollView->createCell(std::get<0>(party), std::get<1>(party));
	}
	DEBUG_MSG("Create Request Parties Paquet");
}

void OnlineMenu::draw()
{
	for (Button* b : buttons)
		b->draw();
}

void OnlineMenu::onClick(uint32_t x, uint32_t y)
{
	for (Button *b : buttons) {
		if (b->isPressed(x, y)) {
			b->onAction();
		}
	}
}

void OnlineMenu::onHover(uint32_t x, uint32_t y)
{
	for (Button *b : buttons) {
		b->onHover(x, y);
	}
}

void OnlineMenu::menu()
{
	std::function<void()> fptr;
	Transformation transformation(350, 525);
	transformation.setScale((float)0.1, (float)0.1);

	fptr = std::bind(&OnlineMenu::createRequestPartiesPaquet, this);
	buttons.push_back(new Button("Refresh", "Button.png", transformation, Color::None, fptr, "Refresh", engine));

	transformation.setPosition(450, 525);
	buttons.push_back(new Button("Join", "Button.png", transformation, Color::None, fptr, "Join", engine));

	transformation.setPosition(550, 525);
	buttons.push_back(new Button("Info", "Button.png", transformation, Color::None, fptr, "Info", engine));
}