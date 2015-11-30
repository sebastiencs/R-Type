#ifndef CREATEGAMEMENU_HH
#define CREATEGAMEMENU_HH

#include "TextField.hh"
#include "Button.hh"
#include "IGraphicEngine.hh"
#include "Transformation.hh"
#include "Color.hh"
#include "OnlineMenu.hh"

class OnlineMenu;

class CreateGameMenu {
public:
	CreateGameMenu(IGraphicEngine *engine, OnlineMenu *_superView);
	virtual ~CreateGameMenu();

	void onCreateGame();

	void draw();

private:
	TextField *serverName;
	TextField *error;
	Button *ok;
	Button *back;
	OnlineMenu *superView;
};

#endif