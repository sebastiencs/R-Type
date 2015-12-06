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

    _callback = func;
    _param = arg;

    if (pthread_create(&_thread, 0, jump, this)) {
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

const Callback_t	&ThreadUnix::getCallback() const
{
  return (_callback);
}

const void		*ThreadUnix::getParam() const
{
  return (_param);
}

void	*jump(void *arg)
{
  ThreadUnix	*threadC = static_cast<ThreadUnix *>(arg);

  Callback_t f = threadC->getCallback();
  const void *param = threadC->getParam();

  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, 0);
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, 0);

  auto value = f(const_cast<void *>(param));

  threadC->setReturn(value);
  threadC->setRunning(false);

  return (value);
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

void		ThreadUnix::setRunning(bool run)
{
  _running = run;
}

bool		ThreadUnix::isRunning() const
{
  return (_running);
}

void		ThreadUnix::setReturn(void *ret)
{
  _return = ret;
}

void		*ThreadUnix::getReturn() const
{
  return (_return);
}

void	ThreadUnix::reRun()
{
  if (!_running) {
    run(_callback, _param);
  }
  else {
    DEBUG_MSG("Try to reRun a running thread");
  }
}
