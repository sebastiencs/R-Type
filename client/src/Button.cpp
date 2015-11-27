#include "Button.hh"


Button::Button(const std::string & text, const std::string& img, const sf::Sprite & sprite, const Transformation & t, const Color & color, std::function<void(void*)> fptr, void* arg)
	: _text(text), _textureName(img), _sprite(sprite), _fptr(fptr), _t(t), _color(color), _arg(arg)
{
}

Button::~Button()
{
}

bool Button::isPressed(uint32_t x, uint32_t y) const
{
	return (x >= _sprite.getPosition().x && x <= ((_sprite.getLocalBounds().width * _sprite.getScale().y) + _sprite.getPosition().x) &&
		y >= _sprite.getPosition().y && y <= ((_sprite.getLocalBounds().height * _sprite.getScale().x) + _sprite.getPosition().y));
}

const std::string& Button::getName() const
{
	return (_text);
}

const std::string & Button::getTextureName() const
{
	return _textureName;
}

const std::function<void(void*)>& Button::getCallback() const
{
	return _fptr;
}

const void * Button::getArgs() const
{
	return _arg;
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
	if (_fptr != nullptr) {
		if (_arg != nullptr)
			_fptr(_arg);
		_fptr(arg);
	}
}

void Button::onHover(uint32_t x, uint32_t y)
{
	if (isPressed(x, y)) {
		_sprite.setColor(sf::Color(Color::Darker.getColor()));
	}
	else
		_sprite.setColor(sf::Color::White);
}
