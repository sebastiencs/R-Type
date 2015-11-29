//
// SemaphoreWin.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Mon Nov 23 12:42:07 2015 chapui_s
// Last update Mon Nov 23 12:42:07 2015 chapui_s
//

#ifndef SEMAPHOREWIN_H_
# define SEMAPHOREWIN_H_

# include "SocketsWin.hh"
# include "ISemaphore.hh"
# include "Debug.hh"

class		SemaphoreWin : public ISemaphore
{
private:
  HANDLE	_sem;

public:
  SemaphoreWin();
  virtual ~SemaphoreWin();

  virtual bool	post();
  virtual bool	wait();
  virtual bool	tryWait();
};

#endif /* !SEMAPHOREWIN_H_ */
