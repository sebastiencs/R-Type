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
  ThreadWin(const Callback_t &, void *);
  virtual ~ThreadWin();

  virtual bool	run(const Callback_t &, void *);
  virtual bool	close();
  virtual bool	join();
};

Callback_t	&save_func(const Callback_t &, int);
void		*jump(void *);

#endif /* !THREADWIN_H_ */
