#include "OptionMenu.hh"
#include "IThread.hh"
#include "Timer.hh"
#include "CheckBox.hh"
#include "ListPlayers.hh"
#include "SystemAudio.hh"

OptionMenu::OptionMenu(IGraphicEngine* eng)
{
	engine = eng;
	VBox = new Box(Orientation::vertical, Transformation(350, 350), "commandBox");
	parser = new ParserIni("conf.ini");
	VBox->setSpacing(25);
	inputMode = "ZQSD";
	muteMusic = false;
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
	try {
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
	muteMusic ? audio.stopMusic() : audio.playMusicRandom();
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

void OptionMenu::menu()
{
	std::function<void()> fptr;
	Transformation transformation(0, 0);

	Box* box1 = new Box(Orientation::horizontal, Transformation(0, 0), "hBox");
	box1->setSpacing(30);
	box1->addDrawable(new TextField("Mute music:\t", transformation, 30, DEFAULT_FONT, Color::White, "Sound", engine));
	fptr = std::bind(&OptionMenu::MuteSound, this);
	box1->addDrawable(new CheckBox("Sound", "CheckBox.png", transformation, Color::None, fptr, "CheckSound", engine));

	Box* box2 = new Box(Orientation::horizontal, Transformation(250, 300), "Box2");
	box2->setSpacing(30);
	box2->addDrawable(new TextField("Input mode:\t", transformation, 30, DEFAULT_FONT, Color::White, "SKeys", engine));
	fptr = std::bind(&OptionMenu::ChangeKeys, this);
	box2->addDrawable(new Button("Keys", "CheckBox.png", transformation, Color::None, fptr, "CheckKeys", engine));
	box2->addDrawable(new TextField(inputMode, transformation, 30, DEFAULT_FONT, Color::White, "TKeys", engine));

	VBox->addDrawable(box1);
	VBox->addDrawable(box2);
}
