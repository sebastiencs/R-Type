//
// ThreadWin.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 15:39:16 2015 chapui_s
// Last update Wed Nov 11 15:39:16 2015 chapui_s
//

#ifndef THREADWIN_H_
# define THREADWIN_H_

# include "SocketsWin.hh"
# include "IThread.hh"

class		ThreadWin : public IThread
{
private:
  HANDLE	_thread;
  bool		_running;

public:
  ThreadWin();
  ThreadWin(const std::function<void *(void *)> &, void *);
  virtual ~ThreadWin();

  virtual bool	run(const std::function<void *(void *)> &, void *);
  virtual bool	close();
  virtual bool	join();
};

std::function<void *(void *)>	&save_func(const std::function<void *(void *)> &, int);
void				*jump(void *);

#endif /* !THREADWIN_H_ */
