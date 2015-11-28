#ifndef MAIN_MENU_FUNCTION_HH_
# define MAIN_MENU_FUNCTION_HH_

# include "DisplayUpdater.hh"

class MainMenu
{
public:
	MainMenu(IGraphicEngine *eng);
	~MainMenu() {}

	void setDisplayOnline();
	void setDisplayOffline();
	void setDisplayOption();
	void myexit();
	void changedMenu();

	int getCurrentPage();

private:
	IGraphicEngine *engine;
	int currentPage;
};

#endif /* !MAIN_MENU_FUNCTION_HH_ */
