//
// EnemyLoader.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Dec 27 01:54:00 2015 chapui_s
// Last update Sun Dec 27 01:54:00 2015 chapui_s
//

#ifndef ENEMYLOADER_H_
# define ENEMYLOADER_H_

# include <string>
# include <memory>
# include "SystemFile.hh"

class Manager;
using Manager_WeakPtr = std::weak_ptr<Manager>;
using Manager_SharedPtr = std::shared_ptr<Manager>;

class		EnemyLoader
{
  Manager_WeakPtr	_manager;
  const std::string	_directory;
  bool			_running;
  ISystemFile_UniquePtr	_SystemFile;

public:
  EnemyLoader(Manager_SharedPtr &&manager, const std::string &dir);
  virtual ~EnemyLoader();

  void	startLoading();
  void	stop();
};

#endif /* !ENEMYLOADER_H_ */
