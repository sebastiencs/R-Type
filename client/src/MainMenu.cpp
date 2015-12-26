#include "MainMenu.hh"
#include "OnlineMenu.hh"
#include "ListPlayers.hh"
#include "CheckBox.hh"
#include "OptionMenu.hh"

MainMenu::MainMenu(IGraphicEngine_SharedPtr eng, NetworkClient_SharedPtr _net)
  : engine(std::move(eng)), net(std::move(_net))
{
	currentPage = 0;
	onlineMenu = std::make_shared<OnlineMenu>(engine);
	creditsMenu = std::make_shared<Credits>(engine);
	optionMenu = std::make_shared<OptionMenu>(engine);

	rTypeLabel = std::make_shared<TextField>("R-Type", Transformation(50, 100), DEFAULT_FONT_SIZE + 30, "Fipps.otf", Color::None, "rtypeLabel", engine);

	uint16_t baseX = 50;
	uint16_t baseY = 500;
	Transformation transformation(baseX, baseY);
	std::function<void()> fptr;

	mainChoiceBox = std::make_shared<Box>(Orientation::vertical, transformation, "mainBox");
	fptr = std::bind(&MainMenu::setDisplayOnline, this);
	onlineButton = std::make_shared<Button>("Online", "onlineButton.png", transformation, Color::None, fptr, "Online", engine);
	mainChoiceBox->addDrawable(onlineButton);
	fptr = std::bind(&MainMenu::setDisplayOffline, this);
	mainChoiceBox->addDrawable(std::make_shared<Button>("Offline", "offlineButton.png", transformation, Color::None, fptr, "Offline", engine));
	fptr = std::bind(&MainMenu::setDisplayOption, this);
	mainChoiceBox->addDrawable(std::make_shared<Button>("Options", "optionButton.png", transformation, Color::None, fptr, "Options", engine));
	fptr = std::bind(&MainMenu::setDisplayCredits, this);
	mainChoiceBox->addDrawable(std::make_shared<Button>("Credits", "creditsButton.png", transformation, Color::None, fptr, "Credits", engine));
	fptr = std::bind(&MainMenu::myexit, this);
	mainChoiceBox->addDrawable(std::make_shared<Button>("Exit", "exitButton.png", transformation, Color::None, fptr, "Exit", engine));
	elements.push_back(mainChoiceBox);

	transformation.setPosition(800, 75);
	fptr = std::bind(&NetworkClient::reconnect, this->net);
	elements.push_back(std::make_shared<Button>("Reconnect", "refreshButton.png", transformation, Color::None, fptr, "Reconnect", engine));

	fptr = std::bind(&MainMenu::draw, this);
	engine->setCallbackFunction(fptr, this);

	mouseCallback fptr2;
	fptr2 = std::bind(&MainMenu::onClick, this, std::placeholders::_1, std::placeholders::_2);
	engine->setMouseClickCallback(fptr2);
	fptr2 = std::bind(&MainMenu::onHover, this, std::placeholders::_1, std::placeholders::_2);
	engine->setMouseMovedCallback(fptr2);
}

MainMenu::~MainMenu() {

  std::cerr << "MAIN MANU DESTRUCTED" << std::endl;
  std::cerr << "Online COUNT: " << onlineMenu.use_count() << std::endl;
  // delete onlineMenu;
  // onlineMenu.reset();
	elements.clear();
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

	if (onlineButton)
		onlineButton->setEnabled(net->getIsConnect());

	for (auto &b : elements)
		if (b->getId() == "Reconnect") {
			if (!net->getIsConnect())
				b->draw();
		}
		else
			b->draw();

	rTypeLabel->draw();
	if (currentPage == 1)
		onlineMenu->draw();
	if (currentPage == 3)
		optionMenu->draw();
	if (currentPage == 4)
		creditsMenu->draw();

	PackageStorage& PC = PackageStorage::getInstance();
	auto &paquet = PC.getAnswersPackage();
	if (paquet) {
		if (paquet->getReturn() == 2) {
			Packager::createFirstUDPPackage(paquet->getData());
			Packager::createFirstUDPPackage(paquet->getData());
			Packager::createFirstUDPPackage(paquet->getData());
			ListPlayers &list = ListPlayers::getInstance();
			list.setId(paquet->getData());
			std::cout << "------------> ID : " << static_cast<int>(list.getId()) << std::endl;
		}
		PC.deleteAnswersPackage();
	}

}

void MainMenu::onClick(uint32_t x, uint32_t y)
{
	for (auto &d : elements) {
		if (ICallback* b = dynamic_cast<ICallback*>(d.get())) {
			if (d->getId() == "Reconnect") {
				if (!net->getIsConnect())
					if (b->onAction(x, y))
						return;
			}
			else
				if (b->onAction(x, y)) {
					return;
				}

		}
	}

	if (currentPage == 1)
		if (onlineMenu->onClick(x, y))
			return;
	if (currentPage == 3)
		if (optionMenu->onClick(x, y))
			return;
}

void MainMenu::onHover(uint32_t x, uint32_t y)
{
	for (auto &d : elements) {
		if (ICallback* b = dynamic_cast<ICallback*>(d.get())) {
			if (d->getId() == "Reconnect") {
				if (!net->getIsConnect())
					b->onHover(x, y);
			}
			else
				b->onHover(x, y);
		}
	}

	if (currentPage == 1)
		onlineMenu->onHover(x, y);
	if (currentPage == 3)
		optionMenu->onHover(x, y);
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
