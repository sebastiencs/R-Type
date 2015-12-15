#include "Mutex.hh"
#include "Debug.hh"

Mutex::Mutex()
{
  DEBUG_MSG("Mutex created");
}

Mutex::~Mutex()
{
  DEBUG_MSG("Mutex deleted");
  tryLock();
  _mutex.unlock();
}

void	Mutex::lock()
{
  _mutex.lock();
}

bool	Mutex::tryLock()
{
  return (_mutex.try_lock());
}

void	Mutex::unlock()
{
  _mutex.unlock();
}
