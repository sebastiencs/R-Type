//
// IMutex.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Dec  9 00:57:57 2015 chapui_s
// Last update Wed Dec  9 00:57:57 2015 chapui_s
//

#ifndef IMUTEX_H_
# define IMUTEX_H_

class		IMutex
{
public:
  virtual ~IMutex() {};

  virtual void	lock() = 0;
  virtual bool	tryLock() = 0;
  virtual void	unlock() = 0;
};

#endif /* !IMUTEX_H_ */
