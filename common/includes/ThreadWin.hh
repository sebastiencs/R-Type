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
  Callback_t	_callback;
  void		*_param;

public:
  ThreadWin();
  ThreadWin(const Callback_t &, void *);
  virtual ~ThreadWin();

  virtual bool	run(const Callback_t &, void *);
  virtual bool	close();
  virtual bool	join();

  const Callback_t	&getCallback() const;
  const void		*getParam() const;

  void		setRunning(bool);
  virtual bool	isRunning() const;
};

void		*jump(void *);

#endif /* !THREADWIN_H_ */
