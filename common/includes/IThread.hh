//
// IThread.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 10 23:32:53 2015 chapui_s
// Last update Tue Nov 10 23:32:53 2015 chapui_s
//

#ifndef ITHREAD_H_
# define ITHREAD_H_

# include <functional>
# include "Debug.hh"

typedef std::function<void *(void *)>	Callback_t;

class		IThread
{
public:
  virtual ~IThread() {};

  virtual bool	run(const Callback_t &func, void *arg) = 0;
  virtual bool	close() = 0;
  virtual bool	join() = 0;
  virtual bool	isRunning() const = 0;
  virtual void	*getReturn() const = 0;
};

#include <memory>
typedef std::shared_ptr<IThread>	IThread_SharedPtr;
typedef std::unique_ptr<IThread>	IThread_UniquePtr;
typedef std::weak_ptr<IThread>		IThread_WeakPtr;

#endif /* !ITHREAD_H_ */
