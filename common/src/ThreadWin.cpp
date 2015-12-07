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
  if (_running) {
    close();
  }
}

bool	ThreadWin::run(const Callback_t &func, void *arg = 0)
{
  if (!_running) {

    _callback = func;
    _param = arg;

    if (!(_thread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(jump), this, 0, nullptr))) {
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

const Callback_t	&ThreadWin::getCallback() const
{
  return (_callback);
}

const void		*ThreadWin::getParam() const
{
  return (_param);
}

void	*jump(void *arg)
{
  ThreadWin	*threadC = static_cast<ThreadWin *>(arg);

  Callback_t f = threadC->getCallback();
  const void *param = threadC->getParam();

  auto value = f(const_cast<void *>(param));

  threadC->setReturn(value);
  threadC->setRunning(false);

  return (value);
}

bool	ThreadWin::close()
{
  if ((TerminateThread(_thread, 0)) == 0)
    DEBUG_MSG("TerminateThread: " + GetLastError());  
  if ((CloseHandle(_thread)) == 0)
    DEBUG_MSG("CloseHandle: " + GetLastError());
  _running = false;
  DEBUG_MSG("ThreadWin ended");
  return (true);
}

bool	ThreadWin::join()
{
  if (WaitForSingleObject(_thread, INFINITE) == WAIT_FAILED) {
    DEBUG_MSG(GetLastError());
    return (false);
  }
  _running = false;
  DEBUG_MSG("ThreadWin ended");
  return (true);
}

void		ThreadWin::setRunning(bool run)
{
  _running = run;
}

bool		ThreadWin::isRunning() const
{
  return (_running);
}

void		ThreadWin::setReturn(void *ret)
{
  _return = ret;
}

void		*ThreadWin::getReturn() const
{
  return (_return);
}

void	ThreadWin::reRun()
{
  if (!_running) {
    run(_callback, _param);
  }
  else {
    DEBUG_MSG("Try to reRun a running thread");
  }
}
