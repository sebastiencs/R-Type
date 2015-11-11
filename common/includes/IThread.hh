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

class		IThread
{
public:
  virtual ~IThread() {};

  virtual bool	run(const std::function<void *(void *)> &, void *) = 0;
  virtual bool	close() = 0;
  virtual bool	join() = 0;
};

#endif /* !ITHREAD_H_ */
