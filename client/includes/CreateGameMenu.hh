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


	const TextField* getServerName() const;
	
	void draw();
	bool onClick(uint32_t x, uint32_t y);
	void onHover(uint32_t x, uint32_t y);
	void getText(const char);

private:
	IGraphicEngine *engine;
	OnlineMenu *superView;

	TextField *serverName;
	TextField *error;
	
	Button *ok;
	Button *back;
};

#endif