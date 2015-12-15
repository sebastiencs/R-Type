//
// Locker.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Mon Dec 14 22:19:13 2015 chapui_s
// Last update Mon Dec 14 22:19:13 2015 chapui_s
//

#ifndef LOCKER_H_
# define LOCKER_H_

# include <iostream>
# include "Debug.hh"

template <typename T>
class		Locker
{
private:
  T	e;
public:

  Locker(T &elem) : e(elem) {
    try {
      elem->lock();
    }
    catch (std::exception &) {
      DEBUG_MSG("Locker: mutex unavailble");
    }
  };

  virtual ~Locker() {
    try {
      e->unlock();
    }
    catch (std::exception &) {
      DEBUG_MSG("Locker: mutex unavailble");
    }
  }
};


#endif /* !LOCKER_H_ */
