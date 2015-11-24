#include "Button.hh"

Button::Button(const std::string & name) : _isPressed(false)
{
}

Button::~Button()
{
}

void Button::setButtonState(bool isPressed)
{
  _isPressed = isPressed;
}

const bool & Button::getButtonState() const
{
  return (_isPressed);
}

void Button::drawButton(const Transformation& t)
{
//  if (_isPressed)
//    GraphicEngine::drawImage("ButtonPressed.png", t, Color::None);
//  else
//    GraphicEngine::drawImage("Button.png", t, Color::None);
}
