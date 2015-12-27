//
// EnemyLoader.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Dec 27 02:00:18 2015 chapui_s
// Last update Sun Dec 27 02:00:18 2015 chapui_s
//

#include "EnemyLoader.hh"
#include "DynamicLib.hh"
#include "Manager.hh"
#include "IOEvent.hh"

EnemyLoader::EnemyLoader(Manager_SharedPtr &&manager, const std::string &dir)
  : _manager(std::move(manager)), _directory(dir), _running(true), _SystemFile(std::make_unique<SystemFile>())
{
}

EnemyLoader::~EnemyLoader()
{
}

void	EnemyLoader::startLoading()
{

  if (_SystemFile->exist(_directory) && _SystemFile->isDirectory(_directory)) {

    while (_running) {

      for (auto &file : _enemies) {

	if (file.second == false) {

	  DynamicLib lib(file.first);
	  auto enemy = lib.getEnemy("getEnemy");
	  //_manager.lock()->pushEnemy(enemy);
	  file.second = true;

	}
      }

      auto &files = _SystemFile->getListFiles(_directory);
      for (auto &file : files) {
	_enemies[file] = false;
      }

      IOEvent::wait(2000);
    }
  }
}

void	EnemyLoader::stop()
{
  _running = false;
}
