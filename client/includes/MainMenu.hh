#ifndef MAIN_MENU_HH_
# define MAIN_MENU_HH_

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

	void draw();

	void onClick(uint32_t x, uint32_t y);

private:
	IGraphicEngine *engine;
	int currentPage;

	std::list<Button* > buttons;
	//OnlineMenu *onlineMenu;
};

#endif /* !MAIN_MENU_HH_ */
