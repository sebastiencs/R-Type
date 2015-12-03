#ifndef LOBBY_HH_
# define LOBBY_HH_

# include "Box.hh"
# include "Sprite.hh"
# include "Button.hh"
# include "TextField.hh"

class LobbyMenu {
public:
	LobbyMenu(IGraphicEngine* engine);
	~LobbyMenu();

	void draw();
	void onHover(uint32_t x, uint32_t y);
	bool onClick(uint32_t x, uint32_t y);

private:
	void leave();
	void ready();

protected:
	IGraphicEngine* engine;
	std::vector<Box*> playerInfo;
	Box* left;
	Box* commands;
	Box* right;
	Button* readyb;
	Button* unReadyb;
};

#endif /* !LOBBY_HH_ */
