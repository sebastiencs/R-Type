//
// Physics.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Dec 13 04:45:51 2015 chapui_s
// Last update Sun Dec 13 04:45:51 2015 chapui_s
//

#ifndef PHYSICS_H_
# define PHYSICS_H_

# include <memory>
# include <iostream>
# include <initializer_list>

class Object;

class		Physics
{
public:
  enum { LOCK, NO_LOCK };

  static int Bullet;

private:

  template <typename... T, typename U>
  static inline bool searchInLists(int lock, U &func, T&... list) {

    std::initializer_list<std::shared_ptr<Object>> init_list;

    if (lock == LOCK) {
      init_list = { (list.findIn(func))... };
    }
    else {
      init_list = { (list.find_if_nolock(func))... };
    }

    bool changed = true;

    for (auto &e : init_list) {

      if (e != nullptr) {
	changed = false;
      }
    }

    return (changed);
  }

public:
  Physics();
  virtual ~Physics();

  template<typename... T, typename U>
  static bool			moveX(int lock, U &elem, uint16_t newX, T&... list) {
    bool changed = true;
    uint8_t mySizeX = elem->getSizeX();
    uint8_t mySizeY = elem->getSizeY();
    uint16_t myY = elem->getY();
    uint8_t myID = elem->getID();

    auto func = [=] (auto &e) {
      if (Bullet || e->getID() != myID) {
	uint16_t x = e->getX();
	uint16_t y = e->getY();
	if (newX < x + e->getSizeX() && newX + mySizeX > x
	    && myY < y + e->getSizeY() && myY + mySizeY > y) {
	  return (true);
	}
      }
      return (false);
    };

    if ((changed = searchInLists(lock, func, list...))) {
      elem->setX(newX);
    }
    return (changed);
  }

  template<typename... T, typename U>
  static bool			moveY(int lock, U &elem, uint16_t newY, T&... list) {
    bool changed = true;
    uint8_t mySizeX = elem->getSizeX();
    uint8_t mySizeY = elem->getSizeY();
    uint16_t myX = elem->getX();
    uint8_t myID = elem->getID();

    auto func = [=] (auto &e) {
      if (Bullet || e->getID() != myID) {
	uint16_t y = e->getY();
	uint16_t x = e->getX();
	if (myX < x + e->getSizeX() && myX + mySizeX > x
	    && newY < y + e->getSizeY() && newY + mySizeY > y) {
	  return (true);
	}
      }
      return (false);
    };

    if ((changed = searchInLists(lock, func, list...))) {
      elem->setY(newY);
    }
    return (changed);
  }

  template<typename... T, typename U>
  static bool			isContact(int lock, U &elem, T&... list) {

    return (!moveX(lock, elem, elem->getX(), list...) || !moveY(lock, elem, elem->getY(), list...));

  }

  template<typename... T, typename U>
  static bool			move(int lock, U &elem, uint16_t newX, uint16_t newY, T&... list) {

    return (!(!moveX(lock, elem, newX, list...) || !moveY(lock, elem, newY, list...)));

  }

};

#endif /* !PHYSICS_H_ */
