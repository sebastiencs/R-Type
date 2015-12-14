//
// Game.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Dec  8 23:13:48 2015 chapui_s
// Last update Tue Dec  8 23:13:48 2015 chapui_s
//

#ifndef GAME_H_
# define GAME_H_

# include <deque>
# include "DisplayUpdater.hh"
# include "ListEnemies.hh"

class PackageStorage;
class ISystemAudio;
class ListPlayers;

# define SHOT_COOLDOWN 200
# define VESSEL_WIDTH 112
# define VESSEL_HEIGHT 49

class		Game
{
private:

	PackageStorage	&_PS;
	ISystemAudio	&_audio;
	ListPlayers	&_LP;
	ListEnemies	_LE;
	IMutex		*_mutex;
	std::deque<Text* > &_nickname;
	std::deque<Sprite* > &_images;
	ITimer		*_timer;
	int			_width;
	int			_height;
	Packager* _packager;
	ITimer* _shotCooldown;
	std::map<uint8_t, std::string> obstacleTypeToSpriteString;

public:
	Game(int width, int height, std::deque<Sprite* > &images, IMutex *mutex, std::deque<Text* > &speudo, Packager* packager);
	virtual ~Game();

	void	run();
	void	handlingNetwork();
	void	updateGraphic();
	void	handlePlayerMovement(const std::deque<UsableKeys>& keysPressed);

	template<typename... Args>
	void drawImage(Args... args) {
		_mutex->lock();
		_images.emplace_back(args...);
		_mutex->unlock();
	};

	template<typename... Args>
	void drawText(Args... args) {
		_mutex->lock();
		_nickname.emplace_back(args...);
		_mutex->unlock();
	};

	template<class T>
	bool	remove_elem(T &elem) {
		if (elem->getX() > _width) {
			return true;
		}
		return false;
	};

};

#endif /* !GAME_H_ */
