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

public:
  ThreadUnix();
  ThreadUnix(const std::function<void *(void *)> &, void *);
  virtual ~ThreadUnix();

  virtual bool	run(const std::function<void *(void *)> &, void *);
  virtual bool	close();
  virtual bool	join();
};

std::function<void *(void *)>	&save_func(const std::function<void *(void *)> &, int);
void				*jump(void *);

#endif /* !THREADUNIX_H_ */
