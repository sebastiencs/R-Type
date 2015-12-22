#include "CreateGameMenu.hh"

CreateGameMenu::CreateGameMenu(IGraphicEngine *engine, OnlineMenu *_superview)
{
	callback fptr;
	textEnteredCallback tptr;
	Color color(255, 255, 255, 255);
	superView = _superview;
	this->engine = engine;

	Transformation t(340, 360);
	tptr = std::bind(&CreateGameMenu::getText, this, std::placeholders::_1);
	engine->setTextEnteredCallback(tptr);
	t.setBounds(200, 30);
	serverName = new TextField("", t, 22, "Fipps.otf", color, "createGameMenuNameField", engine);

	t.setPosition(600, 500);
	t.setBounds(100, 50);
	fptr = std::bind(&OnlineMenu::onCreateGame, superView);
	ok = new Button("Create", "createButton.png", t, Color::None, fptr, "createServerButton2", engine);

	t.setPosition(400, 500);
	t.setBounds(100, 50);
	fptr = std::bind(&OnlineMenu::backButtonGameMenu, superView);
	back = new Button("Back", "cancelButton.png", t, Color::None, fptr, "backButton", engine);

	Transformation t2(300, 330);
	t2.setScale((float)1.3, (float)4.5);
	engine->drawImage("backgroundButton.png", t2);
	sprite = new Sprite("backgroundButton.png", t2, engine, Color::None);
}

CreateGameMenu::~CreateGameMenu()
{
	engine->setTextEnteredCallback(nullptr);
	delete serverName;
	delete ok;
	delete back;
}

const TextField* CreateGameMenu::getServerName() const
{
	return serverName;
}

void CreateGameMenu::draw()
{
	Transformation t(300, 330);
	t.setScale(1.3f, 1.3f);
	engine->drawImage("defaultTextZone.png", t);
	sprite->draw();
	serverName->draw();
	back->draw();
	ok->draw();
}

bool CreateGameMenu::onClick(uint32_t x, uint32_t y)
{
	if (back->onAction(x, y)) {
		return true;
	}
	if (ok->onAction(x, y)) {
		std::cout << "onClick ok" << std::endl;
		return true;
	}
	return sprite->isPressed(x, y);
}

void CreateGameMenu::onHover(uint32_t x, uint32_t y)
{
	back->onHover(x, y);
	ok->onHover(x, y);
}

void CreateGameMenu::getText(const char c)
{
	static auto validChar = [] (const char c) -> bool {
	  return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ');
	};

	if (c == '\b')
	{
		std::string tmp = serverName->getText();
		serverName->setText(tmp.substr(0, tmp.size() - 1));
	}
	else if (c == '\n' || c == '\r')
		superView->onCreateGame();
	else if (validChar(c) && serverName->getText().size() < 20)
		serverName->setText(serverName->getText() + c);
}
