#ifndef ONLINE_MENU_FUNCTION_HH_
# define ONLINE_MENU_FUNCTION_HH_

# include "DisplayUpdater.hh"

class OnlineMenu {
public:
	OnlineMenu(IGraphicEngine* eng, Packager *packager);
	~OnlineMenu() {}

	void menu();
	void createRequestPartiesPaquet();

private:
	IGraphicEngine *engine;
	Packager *packager;
};

#endif // !ONLINE_MENU_FUNCTION_HH_
