//
// Keyboard.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Dec  8 18:29:24 2015 chapui_s
// Last update Tue Dec  8 18:29:24 2015 chapui_s
//

#ifndef KEYBOARD_H_
# define KEYBOARD_H_

#include <SFML/Window.hpp>
#include <map>

class		Keyboard
{
private:

  static std::map<int, sf::Keyboard::Key>	_keys;

  static void _init();

public:

  enum {
    KEY_Z,
    KEY_S,
    KEY_D,
    KEY_Q,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_SPACE
  };

  static bool isKeyPressed(const int code);
};

#endif /* !KEYBOARD_H_ */
