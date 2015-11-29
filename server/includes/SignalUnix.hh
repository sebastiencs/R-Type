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

typedef std::function<void (void)>	Handler_t;
typedef std::map<int, Handler_t>	listHandler;

class		Server;

class		SignalUnix : public ISignal
{
private:
  listHandler	_listHandler;

public:
  SignalUnix();
  virtual ~SignalUnix();

  virtual void	addSignal(int, Handler_t);
  virtual void	callHandler(int sig);
};

void		sig_handler(int);
SignalUnix	*class_save(SignalUnix *ptr_class);

#endif /* !SIGNALUNIX_H_ */
