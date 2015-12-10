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

Game::Game(int width, int height, std::deque<Sprite* > &images, IMutex *mutex, std::deque<Text* > &speudo)
	: _PS(PackageStorage::getInstance()),
	_audio(SystemAudio::getInstance()),
	_LP(ListPlayers::getInstance()),
	_mutex(mutex),
	_nickname(speudo),
	_images(images),
	_timer(new Timer()),
	_width(width),
	_height(height)
{
	DEBUG_MSG("Game created");
	(void)_height;
	_audio.stopMusic();
	_timer->start();
}

Game::~Game()
{
	delete _timer;
	DEBUG_MSG("Game deleted");
}

void	Game::handlingNetwork()
{
	auto &&obstacle = _PS.getObstaclesPackage();
	auto &&shot = _PS.getShotsPackage();
	auto &&coord = _PS.getPlayersPackage();
	auto &&leave = _PS.getLeavePackage();
	auto &&enemy = _PS.getEnemyPackage();

	IPlayer *player;

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
		_PS.deleteEnemyPackage();
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
				Sprite* sprite = new Sprite("bullets-8.png", Transformation(bullet.x, bullet.y));
				drawImage(sprite);
				bullet.x += 15;
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
}

void	Game::run()
{
	handlingNetwork();

	if (_timer->ms() >= MS_REFRESH) { // Don't go faster than GraphicEngine
		updateGraphic();
		_timer->reset();
	}
}
