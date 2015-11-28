#include "DisplayUpdater.hh"

void myexit(void *t)
{
	DEBUG_MSG("Exit");
	exit(EXIT_SUCCESS);
}

void setDisplayOnline(void *arg)
{
	DisplayUpdater *tmp = static_cast<DisplayUpdater *>(arg);
	tmp->setCurrentPageMenu(1);
	DEBUG_MSG("Set Current Page to Online");
}

void setDisplayOffline(void *arg)
{
	DisplayUpdater *tmp = static_cast<DisplayUpdater *>(arg);
	tmp->setCurrentPageMenu(2);
	DEBUG_MSG("Set Current Page to Offline");
}

void setDisplayOption(void *arg)
{
	DisplayUpdater *tmp = static_cast<DisplayUpdater *>(arg);
	tmp->setCurrentPageMenu(3);
	DEBUG_MSG("Set Current Page to Option");
}
