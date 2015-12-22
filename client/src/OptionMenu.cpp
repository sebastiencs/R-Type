#include "OptionMenu.hh"
#include "IThread.hh"
#include "Timer.hh"
#include "CheckBox.hh"
#include "ListPlayers.hh"
#include "SystemAudio.hh"

OptionMenu::OptionMenu(IGraphicEngine* eng)
{
	engine = eng;
	Transformation t(250, 300);
	VBox = new Box(Orientation::vertical, Transformation(200, 500), "commandBox");
	VBox->setSpacing(25);
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

void OptionMenu::menu()
{
	std::function<void()> fptr;
	Transformation transformation(250, 300);

	Box* box1 = new Box(Orientation::horizontal, Transformation(250, 300), "hBox");
	box1->setSpacing(30);
	box1->addDrawable(new TextField("Sound Mute : ", transformation, 30, DEFAULT_FONT, Color::Black, "Sound", engine));
	fptr = std::bind(&OptionMenu::MuteSound, this);
	box1->addDrawable(new CheckBox("Sound", "CheckBox.png", transformation, Color::None, fptr, "CheckSound", engine));

	Box* box2 = new Box(Orientation::horizontal, Transformation(250, 300), "hBox");
	box2->setSpacing(30);
	box2->addDrawable(new TextField("Swap keys (Arrow [ ] - AQSD [X]): ", transformation, 30, DEFAULT_FONT, Color::Black, "SKeys", engine));
	fptr = std::bind(&GraphicEngine::setInputMode(InputMode), engine);
	box2->addDrawable(new CheckBox("Keys", "CheckBox.png", transformation, Color::None, fptr, "CheckKeys", engine));

	VBox->addDrawable(box1);
	VBox->addDrawable(box2);
}
