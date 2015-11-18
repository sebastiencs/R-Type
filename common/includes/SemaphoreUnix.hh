//
// SemaphoreUnix.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 18 22:20:32 2015 chapui_s
// Last update Wed Nov 18 22:20:32 2015 chapui_s
//
#ifndef SEMAPHOREUNIX_H_

# define SEMAPHOREUNIX_H_
# include "ISemaphore.hh"

# include <semaphore.h>
# include "Debug.hh"

class		SemaphoreUnix : public ISemaphore
{
private:
  sem_t		_sem;

public:
  SemaphoreUnix();
  virtual ~SemaphoreUnix();

  virtual bool	post();
  virtual bool	wait();
  virtual bool	tryWait();
};

#endif /* !SEMAPHOREUNIX_H_ */
