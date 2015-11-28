#include "MainMenuFunctions.hh"

void changedMenu(void *arg)
{
	DisplayUpdater *tmp = static_cast<DisplayUpdater *>(arg);
	IGraphicEngine* engine = tmp->getGraphicEngine();

	engine->eraseButton("Refresh");
	engine->eraseButton("Join");
	engine->eraseButton("Info");
}

void myexit(void *arg)
{
	DEBUG_MSG("Exit");
	exit(EXIT_SUCCESS);
}

void setDisplayOnline(void *arg)
{
	DisplayUpdater *tmp = static_cast<DisplayUpdater *>(arg);
	tmp->setCurrentPageMenu(1);
	changedMenu(arg);
	DEBUG_MSG("Set Current Page to Online");
}

void setDisplayOffline(void *arg)
{
	DisplayUpdater *tmp = static_cast<DisplayUpdater *>(arg);
	tmp->setCurrentPageMenu(2);
	changedMenu(arg);
	DEBUG_MSG("Set Current Page to Offline");
}

void setDisplayOption(void *arg)
{
	DisplayUpdater *tmp = static_cast<DisplayUpdater *>(arg);
	tmp->setCurrentPageMenu(3);
	changedMenu(arg);
	DEBUG_MSG("Set Current Page to Option");
}
