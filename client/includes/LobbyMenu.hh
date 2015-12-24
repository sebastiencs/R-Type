#ifndef LOBBY_HH_
# define LOBBY_HH_

// # include "OnlineMenu.hh"
# include "Box.hh"
# include "Sprite.hh"
# include "Button.hh"
# include "TextField.hh"

class OnlineMenu;
class IThread;

using IThread_SharedPtr = std::shared_ptr<IThread>;
//using OnlineMenu_SharedPtr = std::shared_ptr<OnlineMenu>;
using OnlineMenu_WeakPtr = std::weak_ptr<OnlineMenu>;

class LobbyMenu {
public:
	LobbyMenu(IGraphicEngine_SharedPtr engine, OnlineMenu_WeakPtr superview);
	virtual ~LobbyMenu();

	void createRequestListPlayersPaquet();

	//Drawable
	void draw();
	void onHover(uint32_t x, uint32_t y);
	bool onClick(uint32_t x, uint32_t y);

	void setPlayerListChanged(bool changed);
private:
	void ready();
	void updatePlayerList();

protected:
	IGraphicEngine_SharedPtr engine;
	OnlineMenu_WeakPtr _superview;
	// OnlineMenu_SharedPtr _superview;
	IThread_SharedPtr threadReceivedListPlayers;
	IThread_SharedPtr threadReceivedReadyPlayers;
	Box_SharedPtr quadPlayerBox;
	Box_SharedPtr left;
	Box_SharedPtr commands;
	Box_SharedPtr right;
	Button_SharedPtr readyb;
	Button_SharedPtr unReadyb;
	bool playerListChanged;
	int cond;
};

using LobbyMenu_SharedPtr = std::shared_ptr<LobbyMenu>;

#endif /* !LOBBY_HH_ */
