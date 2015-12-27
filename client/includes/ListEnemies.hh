//
// ListEnemies.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Fri Dec 11 23:46:02 2015 chapui_s
// Last update Fri Dec 11 23:46:02 2015 chapui_s
//

#ifndef LISTENEMIES_H_
# define LISTENEMIES_H_

# include <iostream>
# include <list>
# include "Enemy.hh"
# include "ListSecure.hh"

class		ListEnemies
{
  ListSecure<Enemy_SharedPtr> _enemies;

public:

  ListEnemies();
  ListEnemies(const ListEnemies &) = delete;
  virtual ~ListEnemies();

  ListEnemies &operator=(const ListEnemies &) = delete;

  void		addEnemy(Enemy_SharedPtr enemy);
  void		handleEnnemy(const uint8_t id, const uint8_t life, const uint8_t type, const uint16_t x, const uint16_t y);
  void		clearList();

  void		deleteEnemy(const uint8_t id);

  const ListSecure<Enemy_SharedPtr> &getListEnemies() const;
  ListSecure<Enemy_SharedPtr> &getListEnemies();
  Enemy_SharedPtr	getEnemy(const uint8_t id);

};

#endif /* !LISTENEMIES_H_ */
