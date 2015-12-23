//
// Game.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Dec  8 23:15:46 2015 chapui_s
// Last update Tue Dec  8 23:15:46 2015 chapui_s
//

#include "Game.hh"
#include "Paquet/Paquets.hh"
#include "PackageStorage.hh"
#include "SystemAudio.hh"
#include "ListPlayers.hh"
#include "Transformation.hh"
#include "AnimatedSprite.hh"
#include "Sprite.hh"
#include "Keyboard.hh"
#include "Bullet.hh"

Game::Game(int width, int height, ListSecure<Sprite* > &images, ListSecure<Text* > &speudo, Packager* packager)
	: _PS(PackageStorage::getInstance()),
		_audio(SystemAudio::getInstance()),
		_LP(ListPlayers::getInstance()),
		_nickname(speudo),
		_images(images),
		_timer(new Timer()),
		_width(width),
		_height(height),
		_packager(packager),
		_shotCooldown(new Timer()),
		_interval_shot(200),
		_nbShots(1)
{
	obstacleTypeToSpriteString[0] = "enemy0.png"; // normal
	obstacleTypeToSpriteString[1] = "enemy1.png"; // mini boss
	obstacleTypeToSpriteString[2] = "enemy2.png"; // boss

	DEBUG_MSG("Game created");
	(void)_height;
	_audio.stopMusic();
	_timer->start();
	_shotCooldown->start();
}

Game::~Game()
{
	delete _timer;
	if (_shotCooldown)
		delete _shotCooldown;
	DEBUG_MSG("Game deleted");
}

void	Game::handlingNetwork()
{
	auto &&obstacle = _PS.getObstaclesPackage();
	auto &&shot = _PS.getShotsPackage();
	auto &&coord = _PS.getPlayersPackage();
	auto &&leave = _PS.getLeavePackage();
	auto &&enemy = _PS.getEnemyPackage();
	auto &&bonusmalus = _PS.getBonusMalusPackage();
	auto &&life = _PS.getLifePackage();
	auto &&death = _PS.getDeathPackage();
	auto &&attrbonus = _PS.getAttrBonusPackage();

	Player_SharedPtr player;
	Enemy_SharedPtr enem;

	if (obstacle != nullptr) {
		//const PaquetObstacle* p = PackageStorage::getInstance().getObstaclesPackage();
		//graphicEngine->drawImage(obstacleTypeToSpriteString[p->getType()], Transformation(p->getX(), p->getY()));
		//PackageStorage::getInstance().deleteObstaclesPackage();
	}

	if (shot != nullptr) {
		player = _LP.getPlayer(shot->getPlayerID());
		if (player) {
			player->addBullet(std::make_shared<Bullet>(shot->getX(), shot->getY(), shot->getSpeed(), shot->getType(), 8, 7));
		}
		enem = _LE.getEnemy(shot->getPlayerID());
		if (enem) {
			enem->addBullet(std::make_shared<Bullet>(shot->getX(), shot->getY(), shot->getSpeed(), shot->getType(), 8, 7));
		}
		_PS.deleteShotsPackage();
		_audio.playSound(ISystemAudio::SIMPLE_SHOT);
	}

	if (coord != nullptr) {
		player = _LP.getPlayer(coord->getPlayerID());
		if (player) {
			player->setPosition(Position(coord->getX(), coord->getY()));
		}
		_PS.deletePlayersPackage();
	}

	if (enemy != nullptr) {
		DEBUG_MSG("ENEMY !");
		_LE.handleEnnemy(enemy->getID(), enemy->getLife(), enemy->getType(), enemy->getX(), enemy->getY());
		_PS.deleteEnemyPackage();
	}

	if (bonusmalus != nullptr) {
		DEBUG_MSG("Bonus !");
		_BM.push_back(std::make_shared<BonusMalus>(bonusmalus->getID(), bonusmalus->getType(), bonusmalus->getSpeed(), bonusmalus->getX(), bonusmalus->getY()));
		_PS.deleteBonusMalusPackage();
	}

	if (life != nullptr) {
		player = _LP.getPlayer(life->getID());
		if (player) {
			player->setLife(life->getLife());
		}
		enem = _LE.getEnemy(life->getID());
		if (enem) {
			enem->setLife(life->getLife());
		}
		_PS.deleteLifePackage();
	}

	if (death != nullptr) {
		player = _LP.getPlayer(death->getID());
		if (player) {
			DEBUG_MSG(player->getName() << " is dead");
			_deadPlayersName.push_back(player->getName());
			_deadPlayersTimer[player->getName()] = new Timer();
			_deadPlayersTimer[player->getName()]->start();
			if (player != _LP.getListPlayers().front()) {
				_LP.deletePlayer(player.get()->getID());
			}
		}
		enem = _LE.getEnemy(death->getID());
		if (enem) {
			std::cout << "An enemy is dead" << std::endl;
			_LE.deleteEnemy(enem.get()->getID());
		}
		_PS.deleteDeathPackage();
	}

	if (attrbonus != nullptr) {

		uint8_t type = attrbonus->getBonusType();

		if (type == BonusMalus::LIFE) {
			player = _LP.getPlayer(attrbonus->getID());
			if (player) {
				player->setLife(100);
			}
		}
		else {
			if (type == BonusMalus::INTERVAL_SHOT) {
				_interval_shot /= 2;
			}
			else if (type == BonusMalus::DOUBLE_SHOT) {
				_nbShots = 2;
			}
			else if (type == BonusMalus::TRIPLE_SHOT) {
				_nbShots = 3;
			}
			ITimer_SharedPtr timer = std::make_shared<Timer>();
			_bonusState.push_back(std::make_shared<BonusState>(type, timer, attrbonus->getTime()));
			timer->start();
		}

		_PS.deleteAttrBonusPackage();
	}

	if (leave != nullptr) {
		_LP.deletePlayer(leave->getID());
		_PS.deleteLeavePackage();
	}

}

void	Game::updateGraphic()
{
	int i = 0;
	for (auto &&player : _LP.getListPlayers()) {

		if (!player->getBullets().empty()) {
			for (auto &bullet : player->getBullets()) {
				Sprite* sprite = new Sprite("bullets-1.png", Transformation(bullet->getX(), bullet->getY()));
				drawImage(sprite);
				bullet->setX(bullet->getX() + static_cast<uint16_t>((bullet->getSpeed() * GraphicEngine::getDeltaTimeS())));
			}

			auto &bulletList = player->getBullets();
			bulletList.remove_if([this](auto &b) { return (this->remove_elem(b)); });
		}

		Transformation t(player->getPosition().x, player->getPosition().y);		// Player Vessel
		// t.setScale(3.5f, 3.5f);
		Sprite* vesselSprite = new Sprite("vessel" + std::to_string(i++) + ".png", t);
		drawImage(vesselSprite);

		t.setPosition(t.getX(), t.getY() + VESSEL_HEIGHT + 5);		// Player HealthBar
		t.setScale(10.0f, 1.0f);
		Sprite* lifeBG = new Sprite("life-bg.png", t);
		drawImage(lifeBG);
		t.setScale(static_cast<float>((player->getLife() / 10)), 1.0f);
		Sprite* life = new Sprite("life-fg.png", t);
		drawImage(life);

		t.setPosition(t.getX(), player->getPosition().y - 22);		// Player Name
		t.setScale(1.0f, 1.0f);
		Text* text = new Text(player->getName(), DEFAULT_FONT, DEFAULT_FONT_SIZE, t);
		drawText(text);
	}
	for (auto &&enemy : _LE.getListEnemies()) {
		if (!enemy->getBullets().empty()) {
			for (auto &bullet : enemy->getBullets()) {
				Sprite* sprite = new Sprite("bullets-1.png", Transformation(bullet->getX(), bullet->getY()));
				drawImage(sprite);

				if (bullet->getType() > 0) {

					uint16_t y = bullet->getY();
					uint16_t x = bullet->getX();

					auto focused = this->focusOnClosestPlayer(y);

					uint16_t distanceX = 0xFFFF;

					if (focused->getPosition().x < x) {
						distanceX = x - focused->getPosition().x;
					}

					if (focused && focused->getPosition().y < y) {
						if (distanceX < 100) {
							bullet->getY() -= 5;
						}
						else if (distanceX < 400) {
							bullet->getY() -= 3;
						}
					}
					else if (focused && focused->getPosition().y > y) {
						if (distanceX < 100) {
							bullet->getY() += 5;
						}
						if (distanceX < 400) {
							bullet->getY() += 3;
						}
					}
				}

				bullet->setX(bullet->getX() - static_cast<uint16_t>((bullet->getSpeed() * GraphicEngine::getDeltaTimeS())));
			}

			auto &bulletList = enemy->getBullets();
			bulletList.remove_if([this](auto &b) { return (this->remove_bullet_enemy(b)); });
		}
		Transformation t(enemy->getX(), enemy->getY());		// Enemy Sprite
		Sprite* vesselSprite = new Sprite(obstacleTypeToSpriteString[enemy->getType()], t);
		drawImage(vesselSprite);

		t.setPosition(t.getX(), t.getY() - 15);		// Enemy health bar
		t.setScale(10.0f, 1.0f);
		Sprite* lifeBG = new Sprite("life-bg.png", t);
		drawImage(lifeBG);
		t.setScale(static_cast<float>((enemy->getLife() / 10)), 1.0f);
		Sprite* life = new Sprite("life-fg.png", t);
		drawImage(life);
	}

	for (auto &bm : _BM) {	// BONUS/MALUS

		bm->setX(bm->getX() - static_cast<uint16_t>(bm->getSpeed() * GraphicEngine::getDeltaTimeS()));
		Transformation t(bm->getX(), bm->getY());
		t.setScale(0.5f, 0.5f);
		Sprite* bonusMalus = new Sprite("bonus.png", t);
		drawImage(bonusMalus);
	}

	_BM.remove_if([this] (auto &b) { return (this->remove_bonus(b)); });

	if (!_deadPlayersName.empty()) {	// List of dead players
		int32_t y = 15;
		std::list<std::string>::iterator it = _deadPlayersName.begin();
		while (it != _deadPlayersName.end()) {
			if (_deadPlayersTimer[*it] && _deadPlayersTimer[*it]->ms() > DEAD_PLAYER_DRAWTIME) {
				delete _deadPlayersTimer[*it];
				_deadPlayersTimer.erase(*it);
				it = _deadPlayersName.erase(it);
			}
			else {
				Text* deadPlayer = new Text(*it + " died", DEFAULT_FONT, DEFAULT_FONT_SIZE, Transformation(15, y));
				drawText(deadPlayer);
				y += 15;
				++it;
			}
		}
	}
}

const Player_SharedPtr	Game::focusOnClosestPlayer(const uint16_t yOther) const
{
	uint8_t idClosest = 0xFF;
	uint16_t distance = 0xFFFF;

	auto &players = _LP.getListPlayers();

	players.for_each([&] (auto &p) mutable {
			uint16_t tmp = std::abs(p->getPosition().y - yOther);
			if (tmp < distance) {
	idClosest = p->getID();
	distance = tmp;
			}
		});

	return (players.findIn([idClosest] (auto &p) { return (p->getID() == idClosest); }));
}

void Game::handlePlayerMovement(const std::deque<UsableKeys>& keysPressed)
{
	auto player = _LP.getPlayer(_LP.getId());
	bool changed = false;
	bool bullet = false;
	if (!player)
		return;

	Position pos = player->getPosition();
	uint16_t playerVelocity = static_cast<uint16_t>((300 * GraphicEngine::getDeltaTimeS()));
	for (UsableKeys k : keysPressed) {
		switch (k) {
		case UsableKeys::Z:
			if (pos.y > playerVelocity) {
				pos.y -= playerVelocity;
				changed = true;
			}
			break;
		case UsableKeys::Q:
			if (pos.x > playerVelocity) {
				pos.x -= playerVelocity;
				changed = true;
			}
			break;
		case UsableKeys::S:
			if (pos.y < 660) {
				pos.y += playerVelocity;
				changed = true;
			}
			break;
		case UsableKeys::D:
			if (pos.x <= 935) {
				pos.x += playerVelocity;
				changed = true;
			}
			break;
		case UsableKeys::SPACE:
			if (_shotCooldown->ms() > _interval_shot) {
				SystemAudio::getInstance().playSound(ISystemAudio::SIMPLE_SHOT);
				_shotCooldown->reset();
				bullet = true;
			}
			break;
		default:
			break;
		}
	}
	if (changed) {
		changed = Physics::move(Physics::LOCK, player, pos.x, pos.y, _LP.getListPlayers(), _LE.getListEnemies());
		if (changed) {
			_packager->createMovementPackage(_LP.getId(), pos.x, pos.y);
		}
	}
	if (bullet) {
		if (_nbShots == 2 || _nbShots == 3) {
			{
				uint16_t x = pos.x;
				uint16_t y = pos.y;
				_packager->createShotPackage(_LP.getId(), 1, 600, x, y);
				player->addBullet(std::make_shared<Bullet>(x, y, 600, 8, 7)); // les 2 derniers params sont a modifier en fonctions du type de balles.
			}
			{
				uint16_t x = pos.x + VESSEL_WIDTH;
				uint16_t y = pos.y + VESSEL_HEIGHT;
				_packager->createShotPackage(_LP.getId(), 1, 600, x, y);
				player->addBullet(std::make_shared<Bullet>(x, y, 600, 8, 7)); // les 2 derniers params sont a modifier en fonctions du type de balles.
			}
		}
		if (_nbShots != 2) {
			uint16_t x = pos.x + (VESSEL_WIDTH / 2);
			uint16_t y = pos.y + (VESSEL_HEIGHT / 2);
			_packager->createShotPackage(_LP.getId(), 1, 600, x, y);
			player->addBullet(std::make_shared<Bullet>(x, y, 600, 8, 7)); // les 2 derniers params sont a modifier en fonctions du type de balles.
		}
	}
}

void	Game::fixWalkingDead()
{
	auto &&enemies = _LE.getListEnemies();

	enemies.remove_if([] (auto &e) { return (e->getLife() == 0); });
}

int	Game::AmIDead()
{
	auto &&players = _LP.getListPlayers();

	if (players.size()) {

		auto &&player = players.front();

		if (player->getLife() == 0) {
			Packager::createLeavePackage(player->getID());
			SystemAudio::getInstance().playSound(SystemAudio::DEATH);
			return (1);
		}
	}
	return (0);
}

void	Game::removeDeadBonus()
{
	_bonusState.for_each([this] (auto &bonus) {

			if (bonus->timer->ms() >= bonus->time) {

	bonus->expired = 1;

	if (bonus->type == BonusMalus::INTERVAL_SHOT) {
		_interval_shot *= 2;
	}
	else if (bonus->type == BonusMalus::DOUBLE_SHOT) {
		_nbShots = 1;
	}
	else if (bonus->type == BonusMalus::TRIPLE_SHOT) {
		_nbShots = 1;
	}
			}
		});

	_bonusState.remove_if([] (auto &bonus) { return (bonus->expired == 1); });
}

int	Game::run()
{
	removeDeadBonus();
	fixWalkingDead();
	handlingNetwork();

	if (_timer->ms() >= MS_REFRESH) { // Don't go faster than GraphicEngine
		updateGraphic();
		_timer->reset();
	}
	return (AmIDead());
}
