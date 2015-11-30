#ifndef ONLINE_MENU_FUNCTION_HH_
# define ONLINE_MENU_FUNCTION_HH_

# include "DisplayUpdater.hh"
# include "ScrollView.hh"
# include "Packager.hh"

class OnlineMenu {
public:
	OnlineMenu(IGraphicEngine* eng);
	~OnlineMenu();

	void menu();
	void createRequestPartiesPaquet();

	void draw();

	void onClick(uint32_t x, uint32_t y);
	void onHover(uint32_t x, uint32_t y);

	// Join Button
	void joinButton();

private:
	IGraphicEngine *engine;
	ScrollView *scrollView;

	std::list<Button* > buttons;
};

#endif // !ONLINE_MENU_FUNCTION_HH_
