#ifndef MAIN_MENU_HH_
# define MAIN_MENU_HH_

#include "NetworkClient.hh"
#include <iostream>
#include <list>

class OnlineMenu;
class OptionMenu;
class Credits;
class TextField;
class IGraphicEngine;
class Box;
class Drawable;
class Button;

class MainMenu
{
public:
	MainMenu(IGraphicEngine *eng, NetworkClient_SharedPtr net);
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
	NetworkClient_SharedPtr net;
	OnlineMenu *onlineMenu;
	OptionMenu *optionMenu;
	Credits *creditsMenu;
	Button* onlineButton;

	Box* mainChoiceBox;
	TextField *rTypeLabel;
	std::list<Drawable* > elements;
	int currentPage;
};

#endif /* !MAIN_MENU_HH_ */
