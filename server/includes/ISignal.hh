//
// ISignal.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 29 18:44:29 2015 chapui_s
// Last update Sun Nov 29 18:44:29 2015 chapui_s
//

#ifndef ISIGNAL_H_
# define ISIGNAL_H_

class		Server;

class		ISignal
{
public:
  virtual ~ISignal() {};

  virtual void	addSignal(int) = 0;
  virtual void	stopAll() = 0;
};

#endif /* !ISIGNAL_H_ */
