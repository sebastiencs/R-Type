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
	_shotCooldown(new Timer())
{
	obstacleTypeToSpriteString[0] = "enemy0.png"; // normal
	obstacleTypeToSpriteString[1] = "enemy1.png"; // mini boss
	obstacleTypeToSpriteString[2] = "enemy2.png"; // boss

	xBg1 = 0;
	tBg1.setPosition(xBg1, 0);
	bg1 = new Sprite("ingamebg.jpg", tBg1);
	xBg2 = 1920;
	tBg2.setPosition(xBg2, 0);
	bg2 = new Sprite("ingamebg.jpg", tBg2);

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
		DEBUG_MSG("BONUS/MALUS !");
		_PS.deleteBonusMalusPackage();
	}

	if (leave != nullptr) {
		_LP.deletePlayer(leave->getID());
		_PS.deleteLeavePackage();
	}

}

void	Game::updateGraphic()
{
	//UPDATE THE BACKGROUND
	xBg1 -= (uint32_t) (200 * GraphicEngine::getDeltaTimeS());
	if (xBg1 < 1920) {
		xBg1 = 1920;
	}
	tBg1.setPosition(xBg1, 0);
	drawImage(bg1);
	xBg2 -= (uint32_t) (200 * GraphicEngine::getDeltaTimeS());
	if (xBg2 < 1920) {
		xBg2 = 1920;
	}
	tBg2.setPosition(xBg2, 0);
	drawImage(bg2);

	int i = 0;
	for (auto &&player : _LP.getListPlayers()) {

		if (!player->getBullets().empty()) {
			for (auto &bullet : player->getBullets()) {
				Sprite* sprite = new Sprite("bullets-1.png", Transformation(bullet->getX(), bullet->getY()));
				drawImage(sprite);
				bullet->getX() += (uint16_t)(bullet->getSpeed() * GraphicEngine::getDeltaTimeS());
			}

			auto &bulletList = player->getBullets();
			bulletList.remove_if([this](auto &b) { return (this->remove_elem(b)); });
		}

		Transformation t(player->getPosition().x, player->getPosition().y);		// Player Vessel
		t.setScale(3.5, 3.5);
		Sprite* vesselSprite = new Sprite("vessel" + std::to_string(i++) + ".png", t);
		drawImage(vesselSprite);

		t.setPosition(t.getX(), t.getY() + VESSEL_HEIGHT + 5);		// Player HealthBar
		t.setScale(10, 1);
		Sprite* lifeBG = new Sprite("life-bg.png", t);
		drawImage(lifeBG);
		t.setScale((float)(player->getLife() / 10.), 1.);
		Sprite* life = new Sprite("life-fg.png", t);
		drawImage(life);

		t.setPosition(t.getX(), player->getPosition().y - 22);		// Player Name
		t.setScale(1, 1);
		Text* text = new Text(player->getName(), DEFAULT_FONT, DEFAULT_FONT_SIZE, t);
		drawText(text);
	}
	for (auto &&enemy : _LE.getListEnemies()) {
		if (!enemy->getBullets().empty()) {
			for (auto &bullet : enemy->getBullets()) {
				Sprite* sprite = new Sprite("bullets-1.png", Transformation(bullet->getX(), bullet->getY()));
				drawImage(sprite);
				bullet->getX() -= (uint16_t)(bullet->getSpeed() * GraphicEngine::getDeltaTimeS());
			}

			auto &bulletList = enemy->getBullets();
			bulletList.remove_if([this](auto &b) { return (this->remove_bullet_enemy(b)); });
		}
		Transformation t(enemy->getX(), enemy->getY());		// Enemy Sprite
		t.setScale(1.5, 1.5);
		Sprite* vesselSprite = new Sprite(obstacleTypeToSpriteString[enemy->getType()], t);
		drawImage(vesselSprite);

		t.setPosition(t.getX(), t.getY() - 15);		// Enemy health bar
		t.setScale(10., 1.);
		Sprite* lifeBG = new Sprite("life-bg.png", t);
		drawImage(lifeBG);
		t.setScale((float)(enemy->getLife() / 10.), 1.);
		Sprite* life = new Sprite("life-fg.png", t);
		drawImage(life);

	}
}

void Game::handlePlayerMovement(const std::deque<UsableKeys>& keysPressed)
{
	auto player = _LP.getPlayer(_LP.getId());
	bool changed = false;
	bool bullet = false;
	if (!player)
		return;

	Position pos = player->getPosition();
	uint16_t playerVelocity = (uint16_t)(300 * GraphicEngine::getDeltaTimeS());
	for (UsableKeys k : keysPressed) {
		switch (k) {
		case UsableKeys::Z:
			if (pos.y > 10) {
				pos.y -= playerVelocity;
				changed = true;
			}
			break;
		case UsableKeys::Q:
			if (pos.x > 10) {
				pos.x -= playerVelocity;
				changed = true;
			}
			break;
		case UsableKeys::S:
			if (pos.y < 715) {
				pos.y += playerVelocity;
				changed = true;
			}
			break;
		case UsableKeys::D:
			if (pos.x <= 910) {
				pos.x += playerVelocity;
				changed = true;
			}
			break;
		case UsableKeys::SPACE:
			if (_shotCooldown->ms() > SHOT_COOLDOWN) {
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
		uint16_t x = pos.x + (VESSEL_WIDTH / 2);
		uint16_t y = pos.y + (VESSEL_HEIGHT / 2);
		_packager->createShotPackage(_LP.getId(), 1, 600, x, y);
		player->addBullet(std::make_shared<Bullet>(x, y, 600, 8, 7)); // les 2 derniers params sont a modifier en fonctions du type de balles.
	}
}

void	Game::run()
{
	handlingNetwork();

	if (_timer->ms() >= MS_REFRESH) { // Don't go faster than GraphicEngine
		updateGraphic();
		_timer->reset();
	}
}
