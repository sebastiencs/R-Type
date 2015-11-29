#include "OnlineMenuFunctions.hh"

OnlineMenu::OnlineMenu(IGraphicEngine* eng, Packager* packager)
{
	packager = packager;
	engine = eng;
	scrollView = new ScrollView(engine);
}

OnlineMenu::~OnlineMenu()
{
	delete(scrollView);
}

void OnlineMenu::createRequestPartiesPaquet()
{
	packager->createGameListPackage();
	PaquetListParties *list = new PaquetListParties();
	list->addParty("First try", 2);
	list->addParty("Second try", 1);
	for (PartyNB party : list->getParties()) {
		scrollView->createCell(std::get<0>(party), std::get<1>(party));
	}
	DEBUG_MSG("Create Request Parties Paquet");
}

void OnlineMenu::menu()
{
	std::function<void()> fptr;
	Transformation transformation(350, 525);
	transformation.setScale((float)0.1, (float)0.1);

	fptr = std::bind(&OnlineMenu::createRequestPartiesPaquet, this);
	engine->displayButton("Refresh", "Button.png", transformation, Color::None, fptr, "Refresh");

	transformation.setPosition(450, 525);
	engine->displayButton("Join", "Button.png", transformation, Color::None, nullptr, "Join");

	transformation.setPosition(550, 525);
	engine->displayButton("Info", "Button.png", transformation, Color::None, nullptr, "Info");
}
