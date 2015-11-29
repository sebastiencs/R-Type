//
// SignalUnix.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 29 18:46:32 2015 chapui_s
// Last update Sun Nov 29 18:46:32 2015 chapui_s
//

#ifndef SIGNALUNIX_H_
# define SIGNALUNIX_H_

# include <functional>
# include <map>
# include "ISignal.hh"
# include <signal.h>

class		Server;

class		SignalUnix : public ISignal
{
private:
  Server	&_server;

public:
  SignalUnix(Server &);
  virtual ~SignalUnix();

  virtual void	addSignal(int);
  virtual void	stopAll();
};

void		sig_handler(int);
SignalUnix	*class_save(int id, SignalUnix *ptr_class);

#endif /* !SIGNALUNIX_H_ */
