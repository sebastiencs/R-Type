//
// IPlugin.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Dec 27 03:15:46 2015 chapui_s
// Last update Sun Dec 27 03:15:46 2015 chapui_s
//

#ifndef IPLUGIN_H_
# define IPLUGIN_H_

# include "Enemy.hh"

class		IPlugin
{
public:
  IPlugin();
  virtual ~IPlugin() {};

  virtual const Enemy_SharedPtr getEnemy() const = 0;
};

#endif /* !IPLUGIN_H_ */
