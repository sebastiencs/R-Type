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
//	parser = new ParserIni("conf.ini");
//	DEBUG_MSG(parser->getValue("tamere", "name"));
//	parser->setValue("tamere", "name", 42);
//	parser->setText("tamere", "name", "Alex");
//	DEBUG_MSG(parser->getText("tamere", "name"));
	VBox->setSpacing(25);
	inputMode = "ZQSD";
	menu();
}

OptionMenu::~OptionMenu()
{
	if (VBox)
		delete VBox;
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
	static bool state = true;
	ISystemAudio &audio = SystemAudio::getInstance();
	state ? audio.stopMusic() : audio.playMusicRandom();
	state = !state;
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
		inputMode = "Arrows";
		break;
	}
	case 3:
	{
		inputMode = "PAD";
		break;
	}
	default: 
		inputMode = "Unknow";
	}
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
