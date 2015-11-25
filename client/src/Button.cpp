#include "Button.hh"


Button::Button(const std::string & text, const sf::Sprite & sprite, const Transformation & t, const Color & color, std::function<void(void*)> fptr)
	: _text(text), _sprite(sprite), _fptr(fptr), _t(t), _color(color)
{
}

Button::~Button()
{
}

const bool Button::isPressed(const int x, const int y) const
{
	if (x >= _sprite.getPosition().x && x <= (_sprite.getLocalBounds().width + _sprite.getPosition().x) &&
		y >= _sprite.getPosition().y && y <= (_sprite.getLocalBounds().height + _sprite.getPosition().y))
		return true;
	return false;
}

const std::string& Button::getName() const
{
	return (_text);
}

const Transformation & Button::getTransformation() const
{
	return (_t);
}

const Color & Button::getColor() const
{
	return (_color);
}

const sf::Sprite& Button::getSprite() const
{
	return (_sprite);
}

void Button::onAction(void *arg)
{
	if (_fptr != nullptr)
		_fptr(arg);
}
