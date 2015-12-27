//
// enemy1.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Dec 27 03:20:22 2015 chapui_s
// Last update Sun Dec 27 03:20:22 2015 chapui_s
//

#ifndef ENEMY1_H_
# define ENEMY1_H_

# include "../common/includes/IPlugin.hh"

class		Enemy1 : public IPlugin
{
public:
  Enemy1();
  virtual ~Enemy1();

  virtual const Enemy_SharedPtr getEnemy() const;
};


#endif /* !ENEMY1_H_ */
