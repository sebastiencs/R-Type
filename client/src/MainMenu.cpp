#include "MainMenu.hh"

MainMenu::MainMenu(IGraphicEngine *eng, NetworkClient *net)
{
	engine = eng;
	this->net = net;
	currentPage = 0;
	onlineMenu = new OnlineMenu(engine);
	creditsMenu = new Credits(engine);

	rTypeLabel = new TextField("R-Type", Transformation(50, 100), DEFAULT_FONT_SIZE + 30, "Fipps.otf", Color::None, "rtypeLabel", engine);

	uint16_t baseX = 50;
	uint16_t baseY = 500;
	uint16_t offset = 50;
	Transformation transformation(baseX, baseY);
	std::function<void()> fptr;

	fptr = std::bind(&MainMenu::setDisplayOnline, this);
	buttons.push_back(new Button("Online", "onlineButton.png", transformation, Color::None, fptr, "Online", engine));

	transformation.setPosition(baseX, baseY + offset);
	fptr = std::bind(&MainMenu::setDisplayOffline, this);
	buttons.push_back(new Button("Offline", "offlineButton.png", transformation, Color::None, fptr, "Offline", engine));

	transformation.setPosition(baseX, baseY + (offset * 2));
	fptr = std::bind(&MainMenu::setDisplayOption, this);
	buttons.push_back(new Button("Option", "optionButton.png", transformation, Color::None, fptr, "Option", engine));

	transformation.setPosition(baseX, baseY + (offset * 3));
	fptr = std::bind(&MainMenu::setDisplayCredits, this);
	buttons.push_back(new Button("Credits", "creditsButton.png", transformation, Color::None, fptr, "Credits", engine));

	transformation.setPosition(baseX, baseY + (offset * 4));
	fptr = std::bind(&MainMenu::myexit, this);
	buttons.push_back(new Button("Exit", "exitButton.png", transformation, Color::None, fptr, "Exit", engine));

	transformation.setPosition(800, 75);
	fptr = std::bind(&NetworkClient::reconnect, this->net);
	buttons.push_back(new Button("Reconnect", "exitButton.png", transformation, Color::None, fptr, "Reconnect", engine));

	fptr = std::bind(&MainMenu::draw, this);
	engine->setCallbackFunction(fptr, this);

	mouseCallback fptr2;
	fptr2 = std::bind(&MainMenu::onClick, this, std::placeholders::_1, std::placeholders::_2);
	engine->setMouseClickCallback(fptr2);
	fptr2 = std::bind(&MainMenu::onHover, this, std::placeholders::_1, std::placeholders::_2);
	engine->setMouseMovedCallback(fptr2);
}

MainMenu::~MainMenu() {
	for (Button* b : buttons)
		if (b)
			delete b;
	buttons.clear();
	if (rTypeLabel)
		delete rTypeLabel;
}

void MainMenu::changedMenu()
{
	// If button exist, erase it
}

int MainMenu::getCurrentPage()
{
	return currentPage;
}

void MainMenu::draw()
{
	engine->drawImage("menubackground8bit.png", Transformation(0, 0));
	if (!net->getIsConnect())
		engine->drawText("You are not connected", Transformation(750, 50), 12, Color::Red, "Fipps.otf");

	for (Button* b : buttons)
		b->draw();
	rTypeLabel->draw();
	if (currentPage == 1)
		onlineMenu->draw();
	if (currentPage == 4)
		creditsMenu->draw();
}

void MainMenu::onClick(uint32_t x, uint32_t y)
{
	for (Button *b : buttons) {
		if (b->isPressed(x, y)) {
			b->onAction();
		}
	}
	if (currentPage == 1)
		onlineMenu->onClick(x, y);
}

void MainMenu::onHover(uint32_t x, uint32_t y)
{
	for (Button *b : buttons) {
		b->onHover(x, y);
	}

	if (currentPage == 1)
		onlineMenu->onHover(x, y);
}

void MainMenu::setDisplayOnline()
{
	currentPage = 1;
	changedMenu();
	DEBUG_MSG("Set Current Page to Online");
}

void MainMenu::setDisplayOffline()
{
	currentPage = 2;
	changedMenu();
	DEBUG_MSG("Set Current Page to Offline");
}

void MainMenu::setDisplayOption()
{
	currentPage = 3;
	changedMenu();
	DEBUG_MSG("Set Current Page to Option");
}

void MainMenu::setDisplayCredits()
{
	currentPage = 4;
	changedMenu();
	DEBUG_MSG("Set Current Page to Credits");
}

void MainMenu::myexit()
{
	DEBUG_MSG("Exit");
	engine->closeWindow();
}
