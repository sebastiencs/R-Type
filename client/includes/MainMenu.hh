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

using IGraphicEngine_SharedPtr = std::shared_ptr<IGraphicEngine>;
using OnlineMenu_SharedPtr = std::shared_ptr<OnlineMenu>;
using OptionMenu_SharedPtr = std::shared_ptr<OptionMenu>;
using Credits_SharedPtr = std::shared_ptr<Credits>;
using Button_SharedPtr = std::shared_ptr<Button>;

class MainMenu
{
public:
	MainMenu(IGraphicEngine_SharedPtr eng, NetworkClient_SharedPtr net);
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
	IGraphicEngine_SharedPtr engine;
	NetworkClient_SharedPtr net;
	OnlineMenu_SharedPtr onlineMenu;
	OptionMenu_SharedPtr optionMenu;
	Credits_SharedPtr creditsMenu;
	Button_SharedPtr onlineButton;

	Box* mainChoiceBox;
	TextField *rTypeLabel;
	std::list<Drawable* > elements;
	int currentPage;
};

using MainMenu_SharedPtr = std::shared_ptr<MainMenu>;

#endif /* !MAIN_MENU_HH_ */
