//
// ISemaphore.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 18 22:13:17 2015 chapui_s
// Last update Wed Nov 18 22:13:17 2015 chapui_s
//

#ifndef ISEMAPHORE_H_
# define ISEMAPHORE_H_

class		ISemaphore
{
public:
  virtual ~ISemaphore() {};

  virtual bool	post() = 0;
  virtual bool	tryWait() = 0;
  virtual bool	wait() = 0;
};

#endif /* !ISEMAPHORE_H_ */
