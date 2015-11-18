//
// SemaphoreUnix.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 18 22:25:17 2015 chapui_s
// Last update Wed Nov 18 22:25:17 2015 chapui_s
//

#include "SemaphoreUnix.hh"

SemaphoreUnix::SemaphoreUnix()
{
  if (sem_init(&_sem, 0, 0)) {
    DEBUG_MSG("sem_init() failed");
  }
}

SemaphoreUnix::~SemaphoreUnix()
{
  sem_close(&_sem);
}

bool	SemaphoreUnix::post()
{
  if (sem_post(&_sem)) {
    DEBUG_MSG("sem_post() failed");
    return (false);
  }
  return (true);
}

bool	SemaphoreUnix::wait()
{
  if (sem_wait(&_sem)) {
    DEBUG_MSG("sem_wait() failed");
    return (false);
  }
  return (true);
}

bool	SemaphoreUnix::tryWait()
{
  if (sem_trywait(&_sem)) {
    DEBUG_MSG("sem_trywait() failed");
    return (false);
  }
  return (true);
}
