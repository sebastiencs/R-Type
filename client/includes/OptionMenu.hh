#ifndef OPTION_MENU_HH_
# define OPTION_MENU_HH_

# include <chrono>
# include <thread>
# include "DisplayUpdater.hh"
# include "Packager.hh"
# include "LobbyMenu.hh"
# include "IOEvent.hh"
# include "Box.hh"
# include "ParserIni.hh"

class OptionMenu {
public:
	OptionMenu(IGraphicEngine_SharedPtr eng);
	virtual ~OptionMenu();

	void menu();
	void initVariables();

	// Drawable
	void draw();
	bool onClick(uint32_t x, uint32_t y);
	void onHover(uint32_t x, uint32_t y);

	// CheckBox
	void MuteSound();

	//Button
	void ChangeKeys();
	void ChangeName();

	//TextField
	void getText(const char c);

private:
	IGraphicEngine_SharedPtr engine;
	Box_SharedPtr VBox;
	ParserIni_SharedPtr parser;
	TextField* textField;

	std::string inputMode;
	std::string name;
	bool muteMusic;
	bool isWritting;
};

#endif // !OPTION_MENU_HH_
