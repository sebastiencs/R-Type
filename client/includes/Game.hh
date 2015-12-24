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
# include "Enemy.hh"
# include "BonusMalus.hh"
# include "SystemAudio.hh"

class PackageStorage;
class ISystemAudio;
class ListPlayers;

# define VESSEL_WIDTH 80
# define VESSEL_HEIGHT 91
# define DEAD_PLAYER_DRAWTIME 3000

typedef struct bonusState {
  uint8_t type; ITimer_SharedPtr timer; uint16_t time; uint8_t expired;
  bonusState(uint8_t _type, ITimer_SharedPtr &_timer, uint16_t _time) : type(_type), timer(_timer), time(_time), expired(0) { }
} BonusState;

using BonusState_SharedPtr = std::shared_ptr<BonusState>;

class		Game
{
private:

	PackageStorage	&_PS;
	ISystemAudio	&_audio;
	ListPlayers	&_LP;
	ListEnemies	_LE;
	ListSecure<BonusMalus_SharedPtr> _BM;
	ListSecure<Text_SharedPtr> &_nickname;
	ListSecure<Sprite_SharedPtr> &_images;
	IMutex_SharedPtr _mutex;
	ITimer_UniquePtr	_timer;
	int			_width;
	int			_height;
	Packager_SharedPtr _packager;
	ITimer_UniquePtr _shotCooldown;
	std::list<std::string> _deadPlayersName;
	std::map<std::string, Timer* > _deadPlayersTimer;
	std::map<uint8_t, std::string> enemyTypeToSpriteString;
	long _interval_shot;
	ListSecure<BonusState_SharedPtr> _bonusState;
	int _nbShots;

public:
	Game(int width, int height, ListSecure<Sprite_SharedPtr > &images, ListSecure<Text_SharedPtr> &speudo, Packager_SharedPtr packager);
	virtual ~Game();

	int	run();
	void	handlingNetwork();
	void	updateGraphic();
	void	handlePlayerMovement(const std::deque<UsableKeys>& keysPressed);
	void	fixWalkingDead();
	int	AmIDead();
	void	removeDeadBonus();
	const Player_SharedPtr	focusOnClosestPlayer(const uint16_t yOther) const;

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

	template<class T>
	bool	remove_bonus(T &elem) {
		if (elem->getX() > 2000) {
			return true;
		}
		if (Physics::isContact(Physics::LOCK, elem, _LP.getListPlayers())) {
			SystemAudio::getInstance().playSound(ISystemAudio::BONUS);
		  return (true);
		}
		return false;
	};

};

#endif /* !GAME_H_ */
