#include "OptionMenu.hh"
#include "IThread.hh"
#include "Timer.hh"
#include "CheckBox.hh"
#include "TextField.hh"
#include "ListPlayers.hh"
#include "SystemAudio.hh"
#include "PaquetRename.hh"

OptionMenu::OptionMenu(IGraphicEngine* eng)
{
	ListPlayers& PL = ListPlayers::getInstance();
	engine = eng;
	VBox = new Box(Orientation::vertical, Transformation(350, 350), "commandBox");
	parser = new ParserIni("conf.ini");
	textField = new TextField("", Transformation(0, 0), 30, DEFAULT_FONT, Color::None, "NameTextField", engine);

	VBox->setSpacing(25);
	initVariables();
	menu();
}

OptionMenu::~OptionMenu()
{
	if (VBox)
		delete VBox;
	delete parser;
}

void OptionMenu::initVariables()
{
	ISystemAudio &audio = SystemAudio::getInstance();
	ListPlayers& PL = ListPlayers::getInstance();

	inputMode = "ZQSD";
	muteMusic = false;
	isWritting = true;

	try {
	textField->setText(parser->getText("player", "name"));
	PL.getPlayer(PL.getId())->setName(textField->getText());
	inputMode = parser->getText("config", "command");

	if (inputMode == "ZQSD")
		engine->setInputMode(InputMode::ZQSD);
	else if (inputMode == "WASD")
		engine->setInputMode(InputMode::WASD);
	else if (inputMode == "ARROWS")
		engine->setInputMode(InputMode::ARROWS);
	else if (inputMode == "PAD")
		engine->setInputMode(InputMode::PAD);
	else
		engine->setInputMode(InputMode::ZQSD);

	muteMusic  = (parser->getValue("music", "mute") == 1 ? true : false);
	muteMusic ? audio.playMusicRandom() : audio.stopMusic();
	}
	catch (const ParserException& e) { std::cerr << e.what() << std::endl; };
}

void OptionMenu::draw()
{
	if (VBox)
		VBox->draw();
}

bool OptionMenu::onClick(uint32_t x, uint32_t y)
{
	if (VBox->onAction(x, y))
		return true;
	return false;
}

void OptionMenu::onHover(uint32_t x, uint32_t y)
{
	VBox->onHover(x, y);
}

void OptionMenu::MuteSound()
{
	ISystemAudio &audio = SystemAudio::getInstance();
	muteMusic ? audio.stopMusic() : audio.playMusicRandom();
	muteMusic = !muteMusic;
	try {
		parser->setValue("music", "mute", muteMusic);
	}
	catch (const ParserException& e) { std::cerr << e.what() << std::endl; };
}

void OptionMenu::ChangeKeys()
{
	static int state = 0;

	++state;
	state %= 4;

	engine->setInputMode(static_cast<InputMode>(state));

	switch (state) {

	case 0:
	{
		inputMode = "ZQSD";
		break;
	}
	case 1:
	{
		inputMode = "WASD";
		break;
	}
	case 2:
	{
		inputMode = "ARROWS";
		break;
	}
	case 3:
	{
		inputMode = "PAD";
		break;
	}
	default:
		inputMode = "ZQSD";
	}
	try {
		parser->setText("config", "command", inputMode);
	}
	catch (const ParserException& e) { std::cerr << e.what() << std::endl; };
	static_cast<TextField *>(static_cast<Box *>(VBox->getElement("Box2"))->getElement("TKeys"))->setText(inputMode);
}

void OptionMenu::ChangeName()
{
	if (isWritting)
	{
		textEnteredCallback tptr;
		tptr = std::bind(&OptionMenu::getText, this, std::placeholders::_1);
		engine->setTextEnteredCallback(tptr);
	}
	else
	{
		engine->setTextEnteredCallback(nullptr);
		try {
			parser->setText("player", "name", textField->getText());
		}
		catch (const ParserException& e) { std::cerr << e.what() << std::endl; };
		PackageStorage &PS = PackageStorage::getInstance();
		ListPlayers& PL = ListPlayers::getInstance();
		PaquetRename *name = new PaquetRename();

		PL.getPlayer(PL.getId())->setName(textField->getText());
		name->setID(PL.getId());
		name->setName(textField->getText());
		name->createPaquet();
		DEBUG_MSG("SEEEEND");
		PS.storeToSendTCPPackage(name);
	}
	isWritting = !isWritting;
}

void OptionMenu::getText(const char c)
{
	static auto validChar = [](const char c) -> bool {
		return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ');
	};

	if (c == '\b')
	{
		std::string tmp = textField->getText();
		textField->setText(tmp.substr(0, tmp.size() - 1));
	}
	else if (c == '\n')
	{
		static_cast<CheckBox *>(static_cast<Box *>(VBox->getElement("Box2"))->getElement("ChangeName"))->setCheck(0);
		isWritting = !isWritting;
	}
	else if (validChar(c) && textField->getText().size() < 16)
		textField->setText(textField->getText() + c);
}

void OptionMenu::menu()
{
	std::function<void()> fptr;
	Transformation transformation(0, 0);

	Box* box1 = new Box(Orientation::horizontal, Transformation(0, 0), "Box1");
	box1->setSpacing(30);
	box1->addDrawable(new TextField("Mute music:\t", transformation, 30, DEFAULT_FONT, Color::White, "Sound", engine));
	fptr = std::bind(&OptionMenu::MuteSound, this);
	box1->addDrawable(new CheckBox("Sound", "CheckBox.png", transformation, Color::None, fptr, "CheckSound", engine));

	Box* box2 = new Box(Orientation::horizontal, Transformation(0, 0), "Box2");
	box2->setSpacing(30);
	fptr = std::bind(&OptionMenu::ChangeName, this);
	box2->addDrawable(new CheckBox("Change", "CheckBox.png", transformation, Color::None, fptr, "ChangeName", engine));
	box2->addDrawable(new TextField("Rename:\t", transformation, 30, DEFAULT_FONT, Color::White, "Rename", engine));
	box2->addDrawable(textField);

	Box* box3 = new Box(Orientation::horizontal, Transformation(250, 300), "Box3");
	box3->setSpacing(30);
	box3->addDrawable(new TextField("Input mode:\t", transformation, 30, DEFAULT_FONT, Color::White, "SKeys", engine));
	box3->addDrawable(new Button("Keys", "CheckBox.png", transformation, Color::None, fptr, "CheckKeys", engine));
	box3->addDrawable(new TextField(inputMode, transformation, 30, DEFAULT_FONT, Color::White, "TKeys", engine));

	VBox->addDrawable(box2);
	VBox->addDrawable(box1);
	VBox->addDrawable(box3);

	static_cast<CheckBox *>(static_cast<Box *>(VBox->getElement("Box1"))->getElement("CheckSound"))->setCheck(muteMusic);
	static_cast<CheckBox *>(static_cast<Box *>(VBox->getElement("Box2"))->getElement("ChangeName"))->setCheck(isWritting);
}
