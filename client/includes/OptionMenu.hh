#ifndef OPTION_MENU_HH_
# define OPTION_MENU_HH_

# include <chrono>
# include <thread>
# include "DisplayUpdater.hh"
# include "Packager.hh"
# include "LobbyMenu.hh"
# include "IOEvent.hh"
# include "Box.hh"

class OptionMenu {
public:
	OptionMenu(IGraphicEngine* eng);
	~OptionMenu();

	void menu();

	void draw();
	bool onClick(uint32_t x, uint32_t y);
	void onHover(uint32_t x, uint32_t y);

	// CheckBox	
	void MuteSound();

private:
	IGraphicEngine *engine;
	Box* VBox;
};

#endif // !OPTION_MENU_HH_
