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

/**
 * @class  Timer
 * @brief  Implementation de l'interface ITimer en utilisant chrono de la STL (C++11)
 */

typedef std::chrono::high_resolution_clock::time_point	TimePoint_t;

class		Timer : public ITimer
{
private:
  TimePoint_t	_t; /**< Objet qui permet de mesurer le temps*/

public:
  Timer();
  virtual ~Timer();

  virtual void		start();
  virtual void		reset();

  virtual bool		ms(long);
  virtual long		ms();

  virtual bool		ns(long);
  virtual long		ns();

  virtual bool		min(long);
  virtual long		min();
};

#endif /* !TIMER_H_ */
