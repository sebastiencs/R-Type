//
// Keyboard.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Dec  8 18:51:31 2015 chapui_s
// Last update Tue Dec  8 18:51:31 2015 chapui_s
//

#include "Keyboard.hh"

std::map<int, sf::Keyboard::Key>	Keyboard::_keys;

void Keyboard::_init() {
  _keys[KEY_Z] = sf::Keyboard::Z;
  _keys[KEY_S] = sf::Keyboard::S;
  _keys[KEY_D] = sf::Keyboard::D;
  _keys[KEY_Q] = sf::Keyboard::Q;
  _keys[KEY_UP] = sf::Keyboard::Up;
  _keys[KEY_DOWN] = sf::Keyboard::Down;
  _keys[KEY_LEFT] = sf::Keyboard::Left;
  _keys[KEY_RIGHT] = sf::Keyboard::Right;
  _keys[KEY_SPACE] = sf::Keyboard::Space;
}

bool Keyboard::isKeyPressed(int code) {

  static int init = 0;

  if (!init) {
    Keyboard::_init();
    init = 1;
  }

  auto key = _keys.find(code);

  if (key != _keys.end()) {
    return (sf::Keyboard::isKeyPressed(key->second));
  }
  else {
    return (false);
  }
}
