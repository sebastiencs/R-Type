#include "CreateGameMenu.hh"

CreateGameMenu::CreateGameMenu(IGraphicEngine *engine, OnlineMenu *_superview)
{
	//Faut un fond
	Transformation t(500,500);
	t.setBounds(200, 30);
	Color color(255,0,0,1);
	serverName = new TextField("HEY JE SUIS LA", t, 22, "Fipps.otf", color, "createGameMenuNameField", engine);
	t.setPosition(600, 550);
	t.setBounds(100, 50);
	t.setScale(0.3, 0.3);
	callback fptr = std::bind(&CreateGameMenu::onCreateGame, this);
	ok = new Button("Create", "Button.png", t, color, fptr, "createServerButton2", engine);
	superView = _superview;
	t.setPosition(500, 550);
	t.setBounds(100, 50);
	t.setScale(0.3, 0.3);
	fptr = std::bind(&OnlineMenu::backButton, superView);
	back = new Button("Back", "Button.png", t, color, fptr, "backButton", engine);
}

CreateGameMenu::~CreateGameMenu()
{
	delete serverName;
	delete ok;
	delete back;
}

void CreateGameMenu::onCreateGame()
{

}

void CreateGameMenu::draw()
{
	serverName->draw();
	back->draw();
	ok->draw();
}
