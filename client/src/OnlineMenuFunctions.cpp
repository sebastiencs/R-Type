#include "OnlineMenuFunctions.hh"

OnlineMenu::OnlineMenu(IGraphicEngine* eng, Packager* packager)
{
	this->packager = packager;
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
	scrollView->createCell();
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
