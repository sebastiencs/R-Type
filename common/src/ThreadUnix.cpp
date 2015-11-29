//
// ThreadUnix.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 10 23:46:38 2015 chapui_s
// Last update Tue Nov 10 23:46:38 2015 chapui_s
//

#include "ThreadUnix.hh"

ThreadUnix::ThreadUnix()
  : _running(0)
{
}

ThreadUnix::ThreadUnix(const Callback_t &func, void *arg = 0)
  : _running(0)
{
  run(func, arg);
}

ThreadUnix::~ThreadUnix()
{
  if (_running) {
    close();
  }
}

bool	ThreadUnix::run(const Callback_t &func, void *arg = 0)
{
  if (!_running) {

    save_func(func, 1);

    if (pthread_create(&_thread, 0, jump, arg)) {
      DEBUG_MSG("pthread create failed");
      return (false);
    }

    _running = 1;
    DEBUG_MSG("ThreadUnix created");
    return (true);
  }
  DEBUG_MSG("Try to start an already running thread");
  return (false);
}

Callback_t	&save_func(const Callback_t &func = 0, int save = 0)
{
  static Callback_t f = [](void *) -> void * { return (0); };

  if (save) {
    f = func;
  }
  return (f);
}

void	*jump(void *arg)
{
  Callback_t	f = save_func();

  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, 0);
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, 0);
  return (f(arg));
}

bool	ThreadUnix::close()
{
  if (_running) {
    if (pthread_detach(_thread)) {
      DEBUG_MSG("pthread_detach() failed");
    }
    if (pthread_cancel(_thread)) {
      DEBUG_MSG("pthread_cancel failed");
      return (false);
    }
    else {
      _running = 0;
      DEBUG_MSG("ThreadUnix ended (close)");
      return (true);
    }
  }
  return (true);
}

bool	ThreadUnix::join()
{
  if (_running) {
    if (pthread_join(_thread, 0)) {
      DEBUG_MSG("pthread join failed");
      return (false);
    }
    else {
      _running = 0;
      DEBUG_MSG("ThreadUnix ended (join)");
      return (true);
    }
  }
  return (true);
}
