#ifndef MAIN_MENU_HH_
# define MAIN_MENU_HH_

# include "DisplayUpdater.hh"

class OnlineMenu;
class Credits;

class MainMenu
{
public:
	MainMenu(IGraphicEngine *eng);
	~MainMenu();

	void setDisplayOnline();
	void setDisplayOffline();
	void setDisplayOption();
	void setDisplayCredits();
	void myexit();
	void changedMenu();

	int getCurrentPage();

	void draw();

	void onClick(uint32_t x, uint32_t y);
	void onHover(uint32_t x, uint32_t y);

private:
	IGraphicEngine *engine;
	OnlineMenu *onlineMenu;
	Credits *creditsMenu;

	TextField *rTypeLabel;
	std::list<Button* > buttons;
	int currentPage;
};

#endif /* !MAIN_MENU_HH_ */
