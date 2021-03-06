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
# include <memory>

# undef min

class		ITimer
{
public:
  virtual ~ITimer() {};

  virtual void	start() = 0;
  virtual bool	ms(const long) = 0;
  virtual bool	msWait(const long) = 0;
  virtual long	ms() = 0;
  virtual bool	ns(const long) = 0;
  virtual long	ns() = 0;
  virtual bool	sec(const long) = 0;
  virtual long	sec() = 0;
  virtual float	secFloat() = 0;
  virtual bool	min(const long) = 0;
  virtual long	min() = 0;
  virtual void	reset() = 0;
};

typedef std::shared_ptr<ITimer>	ITimer_SharedPtr;
typedef std::unique_ptr<ITimer>	ITimer_UniquePtr;
typedef std::weak_ptr<ITimer>	ITimer_WeakPtr;

#endif /* !ITIMER_H_ */
