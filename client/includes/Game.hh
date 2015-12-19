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
# include "Physics.hh"

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
	ListSecure<Text* > &_nickname;
	ListSecure<Sprite* > &_images;
	IMutex_SharedPtr _mutex;
	ITimer		*_timer;
	int			_width;
	int			_height;
	Packager* _packager;
	ITimer* _shotCooldown;
	std::map<uint8_t, std::string> obstacleTypeToSpriteString;
	uint32_t xBg1;
	uint32_t xBg2;
	Sprite *bg1;
	Sprite *bg2;
	Transformation tBg1;
	Transformation tBg2;

public:
  Game(int width, int height, ListSecure<Sprite* > &images, ListSecure<Text* > &speudo, Packager* packager);
	virtual ~Game();

	void	run();
	void	handlingNetwork();
	void	updateGraphic();
	void	handlePlayerMovement(const std::deque<UsableKeys>& keysPressed);

	template<typename T>
	void drawImage(T args) {
		_images.push_back(args);
	};

	template<typename T>
	void drawText(T args) {
		_nickname.push_back(args);
	};

	template<class T>
	bool	remove_elem(T &elem) {
		if (elem->getX() > _width) {
			return true;
		}
		if (Physics::isContact(Physics::LOCK, elem, _LE.getListEnemies())) {
			return (true);
		}
		return false;
	};

	template<class T>
	bool	remove_bullet_enemy(T &elem) {
		if (elem->getX() > 2000) {
			return true;
		}
		Physics::Bullet = 1;
		if (Physics::isContact(Physics::LOCK, elem, _LP.getListPlayers())) {
		  Physics::Bullet = 0;
		  return (true);
		}
		Physics::Bullet = 0;
		return false;
	};

};

#endif /* !GAME_H_ */
