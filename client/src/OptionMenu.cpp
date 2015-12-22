#include "OptionMenu.hh"
#include "IThread.hh"
#include "Timer.hh"
#include "CheckBox.hh"
#include "ListPlayers.hh"
#include "SystemAudio.hh"

OptionMenu::OptionMenu(IGraphicEngine* eng)
{
	engine = eng;
	Transformation t(350, 150);
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
	Transformation transformation(350, 525);

	Box* box1 = new Box(Orientation::horizontal, Transformation(300, 200), "hBox");
	box1->setSpacing(50);
	box1->addDrawable(new TextField("Sound Mute : ", transformation, 50, DEFAULT_FONT, Color::Black, "Sound", engine));
	fptr = std::bind(&OptionMenu::MuteSound, this);
	box1->addDrawable(new CheckBox("Sound", "CheckBox.png", transformation, Color::None, fptr, "CheckSound", engine));
	
	Box* box2 = new Box(Orientation::horizontal, Transformation(300, 200), "hBox");
	box2->setSpacing(50);
	box2->addDrawable(new TextField("Change Touch ", transformation, 50, DEFAULT_FONT, Color::Black, "Touch", engine));

	VBox->addDrawable(box1);
	VBox->addDrawable(box2);
}
