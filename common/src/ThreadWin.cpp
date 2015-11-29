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

ThreadWin::ThreadWin(const Callback_t &func, void *arg = 0)
  : _running(false),
    _thread(nullptr)
{
  run(func, arg);
}

ThreadWin::~ThreadWin()
{
  close();
}

bool	ThreadWin::run(const Callback_t &func, void *arg = 0)
{
  if (!_running) {
    save_func(func, 1);
    if (!(_thread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(jump), arg, 0, nullptr))) {
      DEBUG_MSG("CreateThread: create thread failed");
      return false;
    }
    _running = true;
    DEBUG_MSG("ThreadWin created");
    return true;
  }
  DEBUG_MSG("Try to start an already running thread");
  return (false);
}

Callback_t	&save_func(const Callback_t &func = 0, int save = 0)
{
  static Callback_t f = [](void *param) -> void * { return (0); };
  if (save)
    f = func;
  return (f);
}

void	*unused(void *param)
{
	return (nullptr);
}

void	*jump(void *arg)
{
  Callback_t f = save_func(unused, 0);
  return (f(arg));
}

bool	ThreadWin::close()
{
  if (!TerminateThread(_thread, EXIT_SUCCESS))
    return (join());
  _running = false;
  DEBUG_MSG("ThreadWin ended");
  return (true);
}

bool	ThreadWin::join()
{
  if (!WaitForSingleObject(_thread, INFINITE)) {
    DEBUG_MSG("WaitForSIngleObject: join failed");
    return (false);
  }
  _running = false;
  DEBUG_MSG("ThreadWin ended");
  return (true);
}
