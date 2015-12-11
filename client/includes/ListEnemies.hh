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
  ListSecure<Enemy *> _enemies;

public:

  ListEnemies();
  ListEnemies(const ListEnemies &) = delete;
  virtual ~ListEnemies();

  ListEnemies &operator=(const ListEnemies &) = delete;

  void		addEnemy(Enemy* player);
  void		clearList();

  void		deleteEnemy(uint8_t id);

  const ListSecure<Enemy *> &getListEnemies() const;
  Enemy*	getEnemy(uint8_t id);

};

#endif /* !LISTENEMIES_H_ */
