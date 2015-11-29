#include "Button.hh"


Button::Button(const std::string & text, const std::string& img, const Transformation & t, const Color & color, callback fptr, const std::string& id, GraphicEngine* engine)
	: _text(text), _textureName(img), _fptr(fptr), _t(t), _color(color), _id(id), _engine(engine)
{
	if (_engine)
	{
		_sprite.setTexture(engine->loadTexture(img));
		engine->transformSprite(_sprite, t, color);
	}
}

Button::~Button()
{
}

bool Button::isPressed(uint32_t x, uint32_t y) const
{
	return (x >= _sprite.getPosition().x && x <= ((_sprite.getLocalBounds().width * _sprite.getScale().x) + _sprite.getPosition().x) &&
		y >= _sprite.getPosition().y && y <= ((_sprite.getLocalBounds().height * _sprite.getScale().y) + _sprite.getPosition().y));
}

const std::string& Button::getName() const
{
	return (_text);
}

const std::string & Button::getTextureName() const
{
	return _textureName;
}

const callback& Button::getCallback() const
{
	return _fptr;
}

const Transformation & Button::getTransformation() const
{
	return (_t);
}

const Color & Button::getColor() const
{
	return (_color);
}

void Button::draw()
{
	_engine->drawImage(_text, _t, _color);
}

const std::string& Button::getId() const
{
	return _id;
}


const sf::Sprite& Button::getSprite() const
{
	return (_sprite);
}

void Button::onAction()
{
	if (_fptr != nullptr)
		_fptr();
}

void Button::onHover(uint32_t x, uint32_t y)
{
	if (isPressed(x, y)) {
		_sprite.setColor(sf::Color(Color::Darker.getColor()));
	}
	else
		_sprite.setColor(sf::Color::White);
}
