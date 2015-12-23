#ifndef CREATEGAMEMENU_HH
#define CREATEGAMEMENU_HH

#include "TextField.hh"
#include "Button.hh"
#include "IGraphicEngine.hh"
#include "Transformation.hh"
#include "Color.hh"
#include "OnlineMenu.hh"
#include "Sprite.hh"

class OnlineMenu;

class CreateGameMenu {
public:
	CreateGameMenu(IGraphicEngine_SharedPtr engine, OnlineMenu *_superView);
	virtual ~CreateGameMenu();


	const TextField_SharedPtr &getServerName() const;

	void draw();
	bool onClick(uint32_t x, uint32_t y);
	void onHover(uint32_t x, uint32_t y);
	void getText(const char);

private:
	IGraphicEngine_SharedPtr engine;
	OnlineMenu *superView;

	TextField_SharedPtr serverName;

	Button_SharedPtr ok;
	Button_SharedPtr back;
	Sprite_SharedPtr sprite;
};

#endif
