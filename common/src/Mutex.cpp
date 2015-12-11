#include "Mutex.hh"
#include "Debug.hh"

Mutex::Mutex()
{
  DEBUG_MSG("Mutex created");
}

Mutex::~Mutex()// TODO: plante chez moi sur un ALT-f4 ("unlock of unowned mutex"). Clement
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
