//
// Timer.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 15 23:46:59 2015 chapui_s
// Last update Sun Nov 15 23:46:59 2015 chapui_s
//

#ifndef TIMER_H_
# define TIMER_H_

# include <chrono>
# include "ITimer.hh"

# undef min

class		Timer : public ITimer
{
private:
  std::chrono::high_resolution_clock::time_point	_t;

public:
  Timer();
  virtual ~Timer();

  virtual void		start();
  virtual void		reset();

  // Is n milliseconds expired from start() ( or reset() )
  virtual bool		ms(long);
  virtual bool		msWait(long);
  // return n milliseconds from start() ( or reset() )
  virtual long		ms();

  // Same in nanoseconds
  virtual bool		ns(long);
  virtual long		ns();

  // Same in minutes
  virtual bool		min(long);
  virtual long		min();
};

#endif /* !TIMER_H_ */
