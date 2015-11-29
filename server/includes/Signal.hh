//
// Signal.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 29 16:35:35 2015 chapui_s
// Last update Sun Nov 29 16:35:35 2015 chapui_s
//

#ifndef SIGNAL_H_
# define SIGNAL_H_

# include <functional>
# include <map>
# include <signal.h>

class		Server;

class		Signal
{
private:
  Server	&_server;

public:
  Signal(Server &);
  virtual ~Signal();

  void		addSignal(int);
  void		stopAll();
};

void		sig_handler(int);
Signal		*class_save(int id, Signal *ptr_class);

#endif /* !SIGNAL_H_ */
