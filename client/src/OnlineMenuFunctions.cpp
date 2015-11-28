#include "OnlineMenuFunctions.hh"

OnlineMenu::OnlineMenu(IGraphicEngine* eng, Packager* packager)
{
	packager = packager;
	engine = eng;
}

void OnlineMenu::createRequestPartiesPaquet()
{
	packager->createGameListPackage();
	DEBUG_MSG("Create Request Parties Paquet");
}

void OnlineMenu::menu()
{
	Transformation t1(350, 525);

	t1.setScale((float)0.1, (float)0.1);
	std::function<void()> fptr = std::bind(&OnlineMenu::createRequestPartiesPaquet, this);
	engine->displayButton("Refresh", "Button.png", t1, Color::None, fptr);
	t1.setPosition(450, 525);
	engine->displayButton("Join", "Button.png", t1, Color::None, nullptr);
	t1.setPosition(550, 525);
	engine->displayButton("Info", "Button.png", t1, Color::None, nullptr);
}
