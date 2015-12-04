#ifndef LOBBY_HH_
# define LOBBY_HH_

# include "OnlineMenu.hh"
# include "Box.hh"
# include "Sprite.hh"
# include "Button.hh"
# include "TextField.hh"

class LobbyMenu {
public:
	LobbyMenu(IGraphicEngine* engine, OnlineMenu *superview);
	~LobbyMenu();

	void draw();
	void onHover(uint32_t x, uint32_t y);
	bool onClick(uint32_t x, uint32_t y);

private:
	void ready();

protected:
	IGraphicEngine* engine;
	std::vector<Box*> playerInfo;
	OnlineMenu *_superview;
	Box* left;
	Box* commands;
	Box* right;
	Button* readyb;
	Button* unReadyb;
};

#endif /* !LOBBY_HH_ */
