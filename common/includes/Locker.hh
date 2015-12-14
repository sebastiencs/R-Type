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

template <typename T>
class		Locker
{
private:
  T		&e;
public:
  Locker(T *elem) : e(*elem) {
    elem->lock();
  };
  Locker(T &elem) : e(elem) {
    elem.lock();
  };
  Locker(T &&elem) : e(elem) {
    elem.lock();
  };
  virtual ~Locker() {
    e.unlock();
  }
};


#endif /* !LOCKER_H_ */
