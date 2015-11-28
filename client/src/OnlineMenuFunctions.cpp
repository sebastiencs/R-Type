#include "OnlineMenuFunctions.hh"

void createRequestPartiesPaquet(void *arg)
{
	Packager *tmp = static_cast<Packager *>(arg);
	tmp->createGameListPackage();
	DEBUG_MSG("Create Request Parties Paquet");
}

void onlineMenu(void *arg) 
{
	DisplayUpdater *tmp = static_cast<DisplayUpdater *>(arg);
	IGraphicEngine* engine = tmp->getGraphicEngine();
	Transformation t1(350, 525);

	t1.setScale((float)0.1, (float)0.1);
	engine->displayButton("Refresh", "Button.png", t1, Color::None, &createRequestPartiesPaquet, arg);
	t1.setPosition(450, 525);
	engine->displayButton("Join", "Button.png", t1, Color::None, nullptr);
	t1.setPosition(550, 525);
	engine->displayButton("Info", "Button.png", t1, Color::None, nullptr);
}
