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
	OptionMenu(IGraphicEngine* eng);
	~OptionMenu();

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

private:
	IGraphicEngine *engine;
	Box* VBox;
	ParserIni* parser;

	std::string inputMode;
	bool muteMusic;
};

#endif // !OPTION_MENU_HH_
