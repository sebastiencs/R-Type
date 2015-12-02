#include "Button.hh"
#include "Debug.hh"

Button::Button(const std::string & text, const std::string& img, const Transformation & t, const Color & color, callback fptr, const std::string& id, IGraphicEngine* engine)
	: _engine(dynamic_cast<GraphicEngine*>(engine)), _color(color), _text(text), _textureName(img), _fptr(fptr)
{
	_transformation = t;
	_id = id;
	if (_engine)
	{
		_sprite.setTexture(_engine->loadTexture(_textureName));
		_engine->transformSprite(_sprite, _transformation, _color);
	}
	_transformation.setBounds(_sprite.getGlobalBounds().width, _sprite.getGlobalBounds().height);
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

const Color & Button::getColor() const
{
	return (_color);
}

void Button::setTransformation(const Transformation & t)
{
	_transformation = t;
	_engine->transformSprite(_sprite, _transformation);
}

void Button::draw()
{
	if (_engine)
		_engine->drawSprite(_sprite);
	else
		DEBUG_MSG("No instance of GraphicEngine");
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
