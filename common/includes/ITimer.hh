//
// ITimer.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 15 23:43:49 2015 chapui_s
// Last update Sun Nov 15 23:43:49 2015 chapui_s
//

#ifndef ITIMER_H_
# define ITIMER_H_

# include <iostream>

# undef min

class		ITimer
{
public:
  virtual ~ITimer() {};

  virtual void	start() = 0;
  virtual bool	ms(long) = 0;
  virtual bool	msWait(long) = 0;
  virtual long	ms() = 0;
  virtual bool	ns(long) = 0;
  virtual long	ns() = 0;
  //virtual bool	min(long) = 0;
  //virtual long	min() = 0;
  virtual void	reset() = 0;
};


#endif /* !ITIMER_H_ */
