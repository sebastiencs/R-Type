#include "CreateGameMenu.hh"

CreateGameMenu::CreateGameMenu(IGraphicEngine *engine, OnlineMenu *_superview)
{
	//Faut un fond
	callback fptr;
	textEnteredCallback tptr;
	Transformation t(500,500);
	Color color(255,0,0,255);
	superView = _superview;
	this->engine = engine;

	tptr = std::bind(&CreateGameMenu::getText, this, std::placeholders::_1);
	engine->setTextEnteredCallback(tptr);
	t.setBounds(200, 30);
	serverName = new TextField("", t, 22, "Fipps.otf", color, "createGameMenuNameField", engine);

	t.setPosition(600, 550);
	t.setBounds(100, 50);
	t.setScale((float)0.3, (float)0.3);
	fptr = std::bind(&CreateGameMenu::onCreateGame, this);
	ok = new Button("Create", "Button.png", t, Color::None, fptr, "createServerButton2", engine);

	t.setPosition(500, 550);
	t.setBounds(100, 50);
	t.setScale((float)0.3, (float)0.3);
	fptr = std::bind(&OnlineMenu::backButton, superView);
	back = new Button("Back", "Button.png", t, Color::None, fptr, "backButton", engine);
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

void CreateGameMenu::onClick(uint32_t x, uint32_t y)
{
	if (back->isPressed(x, y)) {
		back->onAction();
		return;
	}
	if (ok->isPressed(x, y)) {
		ok->onAction();
	}
}

void CreateGameMenu::onHover(uint32_t x, uint32_t y)
{
	back->onHover(x, y);
	ok->onHover(x, y);
}

void CreateGameMenu::getText(const char c)
{
	if (c == 8)
	{
		std::string tmp = serverName->getText();
		serverName->setText(tmp.substr(0, tmp.size() - 1));
	}
	else
		serverName->setText(serverName->getText() + c);
}
