//
// Mutex.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Dec  9 00:59:58 2015 chapui_s
// Last update Wed Dec  9 00:59:58 2015 chapui_s
//

#ifndef MUTEX_H_
# define MUTEX_H_

# include "IMutex.hh"
# include <mutex>

class		Mutex : public IMutex
{
private:
  std::mutex	_mutex;

public:
  Mutex();
  virtual ~Mutex();

  virtual void	lock();
  virtual bool	tryLock();
  virtual void	unlock();
};

#endif /* !MUTEX_H_ */
