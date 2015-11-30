#include "MainMenu.hh"

MainMenu::MainMenu(IGraphicEngine *eng)
{
	engine = eng;
	currentPage = 0;
	onlineMenu = new OnlineMenu(engine);
	onlineMenu->menu();

	rTypeLabel = new TextField("R-Type", Transformation(100, 100), DEFAULT_FONT_SIZE + 10, "Fipps.otf", Color::None, "rtypeLabel", engine);

	Transformation transformation(50, 200);
	std::function<void()> fptr;
	fptr = std::bind(&MainMenu::setDisplayOnline, this);
	buttons.push_back(new Button("Online", "onlineButton.png", transformation, Color::None, fptr, "Online", engine));

	transformation.setPosition(50, 300);
	fptr = std::bind(&MainMenu::setDisplayOffline, this);
	buttons.push_back(new Button("Offline", "offlineButton.png", transformation, Color::None, fptr, "Offline", engine));

	transformation.setPosition(50, 400);
	fptr = std::bind(&MainMenu::setDisplayOption, this);
	buttons.push_back(new Button("Option", "optionButton.png", transformation, Color::None, fptr, "Option", engine));

	transformation.setPosition(50, 500);
	fptr = std::bind(&MainMenu::myexit, this);
	buttons.push_back(new Button("Exit", "exitButton.png", transformation, Color::None, fptr, "Exit", engine));

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
	engine->drawImage("menubackground.png", Transformation(0, 0));
	for (Button* b : buttons)
		b->draw();
	rTypeLabel->draw();
	if (currentPage == 1) {
		onlineMenu->draw();
	}
}

void MainMenu::onClick(uint32_t x, uint32_t y)
{
	for (Button *b : buttons) {
		if (b->isPressed(x, y)) {
			b->onAction();
		}
	}
	if (currentPage == 1) {
		onlineMenu->onClick(x, y);
	}
}

void MainMenu::onHover(uint32_t x, uint32_t y)
{
	for (Button *b : buttons) {
		b->onHover(x, y);
	}

	if (currentPage == 1) {
		onlineMenu->onHover(x, y);
	}
}

void MainMenu::setDisplayOnline()
{
	currentPage = 1;
	changedMenu();
	DEBUG_MSG("Set Current Page to Online");
}

void MainMenu::setDisplayOffline()
{
	currentPage = 4;
	changedMenu();
	DEBUG_MSG("Set Current Page to Offline");
}

void MainMenu::setDisplayOption()
{
	currentPage = 3;
	changedMenu();
	DEBUG_MSG("Set Current Page to Option");
}

void MainMenu::myexit()
{
	DEBUG_MSG("Exit");
	exit(EXIT_SUCCESS);
}