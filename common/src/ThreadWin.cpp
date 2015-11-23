//
// ThreadWin.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 15:47:25 2015 chapui_s
// Last update Wed Nov 11 15:47:26 2015 chapui_s
//

#include "ThreadWin.hh"

ThreadWin::ThreadWin()
  : _running(false),
    _thread(nullptr)
{
}

ThreadWin::ThreadWin(const std::function<void *(void *)> &func, void *arg = 0)
  : _running(false),
    _thread(nullptr)
{
  run(func, arg);
}

ThreadWin::~ThreadWin()
{
  close();
}

bool	ThreadWin::run(const std::function<void *(void *)> &func, void *arg = 0)
{
  if (!_running) {
    save_func(func, 1);
	/*if (!(_thread = CreateThread(nullptr, 0, nullptr, arg, 0, nullptr))) {
      DEBUG_MSG("CreateThread: create thread failed");
      return false;
    }*/
    _running = true;
    DEBUG_MSG("ThreadWin created");
    return true;	      
  }
  DEBUG_MSG("Try to start an already running thread");
  return (false);
}

std::function<void *(void *)>	&save_func(const std::function<void *(void *)> &func = 0, int save = 0)
{
  static std::function<void *(void *)> f = [](void *param) -> void * { return (0); };
  if (save)
    f = func;
  return (f);
}

void	*jump(void *arg)
{
	/*std::function<void *(void *)>	f = save_func();
	return (f(arg));*/
	return 0;
}

bool	ThreadWin::close()
{
  /*if (TerminateThread(_thread, EXIT_SUCCESS))
    return (join());*/
  _running = false;
  DEBUG_MSG("ThreadWin ended");
  return (true);
}

bool	ThreadWin::join()
{
 /* if (!WaitForSingleObject(_thread, INFINITE)) {
    DEBUG_MSG("WaitForSIngleObject: join failed");
    return (false);
  }*/
  _running = false;
  DEBUG_MSG("ThreadWin ended");
  return (true);
}
