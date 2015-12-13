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

Game::Game(int width, int height, std::deque<Sprite* > &images, IMutex *mutex, std::deque<Text* > &speudo, Packager* packager)
	: _PS(PackageStorage::getInstance()),
	_audio(SystemAudio::getInstance()),
	_LP(ListPlayers::getInstance()),
	_mutex(mutex),
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

	Player *player;

	if (obstacle != nullptr) {
		//const PaquetObstacle* p = PackageStorage::getInstance().getObstaclesPackage();
		//graphicEngine->drawImage(obstacleTypeToSpriteString[p->getType()], Transformation(p->getX(), p->getY()));
		//PackageStorage::getInstance().deleteObstaclesPackage();
	}

	if (shot != nullptr) {
		player = _LP.getPlayer(shot->getPlayerID());
		if (player) {
			player->addBullet(Position(shot->getX(), shot->getY()));
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
	int i = 0;
	for (auto &&player : _LP.getListPlayers()) {

		if (!player->getBullets().empty()) {
			for (auto &bullet : player->getBullets()) {
				Sprite* sprite = new Sprite("bullets-1.png", Transformation(bullet.x, bullet.y));
				drawImage(sprite);
				bullet.x += (uint16_t)(600 * GraphicEngine::getDeltaTimeS());
			}

			auto &bulletList = player->getBullets();
			bulletList.remove_if([this](auto &b) { return (this->remove_elem(b)); });
		}

		Transformation t(player->getPosition().x, player->getPosition().y);
		t.setScale(3.5, 3.5);
		Sprite* vesselSprite = new Sprite("vessel" + std::to_string(i++) + ".png", t);
		drawImage(vesselSprite);
		t.setPosition(t.getX(), t.getY() - 22);
		t.setScale(1, 1);
		Text* text = new Text(player->getName(), DEFAULT_FONT, DEFAULT_FONT_SIZE, t);
		drawText(text);
	}
	for (auto &&enemy : _LE.getListEnemies()) {
		Transformation t(enemy->getX(), enemy->getY());
		t.setScale(1.5, 1.5);
		//DEBUG_MSG("type: " << (int)enemy->getType());
		Sprite* vesselSprite = new Sprite(obstacleTypeToSpriteString[enemy->getType()], t);
		drawImage(vesselSprite);
	}
}

void Game::handlePlayerMovement(const std::deque<UsableKeys>& keysPressed)
{
	Player *player = _LP.getPlayer(_LP.getId());
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
		for (Player* player : _LP.getListPlayers()) {
			if (player->getID() != _LP.getId()) {
				Position playerPos = player->getPosition();
				if (pos.x < playerPos.x + VESSEL_WIDTH && pos.x + VESSEL_WIDTH > playerPos.x &&
					pos.y < playerPos.y + VESSEL_HEIGHT && pos.y + VESSEL_HEIGHT > playerPos.y) {
					changed = false;
					break;
				}
			}
		}
		if (changed) {
			player->setPosition(pos);
			_packager->createMovementPackage(_LP.getId(), pos.x, pos.y);
		}
	}
	if (bullet) {
		_packager->createShotPackage(_LP.getId(), 1, pos.x, pos.y);
		player->addBullet(Position(pos.x, pos.y));
	}

		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		//	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && pos.y >= 10) {
		//		// Si S est appuyer en meme temps le mec bouge pas.
		//		pos.y -= playerVelocity;
		//		changed = true;
		//	}
		//}
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		//	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && pos.x >= 10) {
		//		pos.x -= playerVelocity;
		//		changed = true;
		//	}
		//}
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		//	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && pos.y <= 715) {
		//		pos.y += playerVelocity;
		//		changed = true;
		//	}
		//}
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		//	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && pos.x <= 910) {
		//		pos.x += playerVelocity;
		//		changed = true;
		//	}
		//}
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _shotCooldown->ms() > SHOT_COOLDOWN) {
		//	audio.playSound(ISystemAudio::SIMPLE_SHOT);
		//	_shotCooldown->reset();
		//	bullet = true;
		//}
		//if (changed) {
		//	player->setPosition(pos);
		//	_packager->createMovementPackage(LP.getId(), pos.x, pos.y);
		//}
		//if (bullet) {
		//	_packager->createShotPackage(LP.getId(), 1, pos.x, pos.y);
		//	player->addBullet(Position(pos.x, pos.y));
		//}

}

void	Game::run()
{
	handlingNetwork();

	if (_timer->ms() >= MS_REFRESH) { // Don't go faster than GraphicEngine
		updateGraphic();
		_timer->reset();
	}
}
