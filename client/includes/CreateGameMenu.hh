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
	CreateGameMenu(IGraphicEngine_SharedPtr engine, OnlineMenu_SharedPtr _superView);
	virtual ~CreateGameMenu();


	const TextField_SharedPtr &getServerName() const;

	void draw();
	bool onClick(const uint32_t x, const uint32_t y);
	void onHover(const uint32_t x, const uint32_t y);
	void getText(const char);

private:
	IGraphicEngine_SharedPtr engine;
	OnlineMenu_SharedPtr superView;

	TextField_SharedPtr serverName;

	Button_SharedPtr ok;
	Button_SharedPtr back;
	Sprite_SharedPtr sprite;
};

using CreateGameMenu_SharedPtr = std::shared_ptr<CreateGameMenu>;

#endif
