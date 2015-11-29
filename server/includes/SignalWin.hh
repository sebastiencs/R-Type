//
// SignalWin.hh for epitech in /home/bresci_b/R-Type
//
// Made by bresci_b
// Login   <bresci_b@epitech.eu>
//
// Started on  Sun Nov 29 18:46:32 2015 bresci_b
// Last update Sun Nov 29 18:46:32 2015 bresci_b
//

#ifndef SIGNALWIN_H_
# define SIGNALWIN_H_

# include "Debug.hh"
# include "Server.hh"
# include "ISignal.hh"

class		Server;

class		SignalWin : public ISignal
{
private:
  Server	&_server;

public:
  SignalWin(Server &);
  virtual ~SignalWin();

  virtual void	addSignal(int);
  virtual void	stopAll();
};

void		sig_handler(int);
SignalWin	*class_save(int id, SignalWin *ptr_class);

#endif /* !SIGNALWIN_H_ */
