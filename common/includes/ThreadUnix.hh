//
// ThreadUnix.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 10 23:38:28 2015 chapui_s
// Last update Tue Nov 10 23:38:28 2015 chapui_s
//

#ifndef THREADUNIX_H_
# define THREADUNIX_H_

# include <pthread.h>
# include "IThread.hh"

class		ThreadUnix : public IThread
{
private:
  pthread_t	_thread;
  bool		_running;
  Callback_t	_callback;
  void		*_param;
  void		*_return;

public:
  ThreadUnix();
  ThreadUnix(const Callback_t &func, void *arg);
  virtual ~ThreadUnix();

  virtual bool	run(const Callback_t &func, void *arg);
  virtual bool	close();
  virtual bool	join();

  const Callback_t	&getCallback() const;
  const void		*getParam() const;

  void		setRunning(bool);
  virtual bool	isRunning() const;

  void		setReturn(void *);
  virtual void	*getReturn() const;
  virtual void	reRun();
};

void		*jump(void *);

#endif /* !THREADUNIX_H_ */
