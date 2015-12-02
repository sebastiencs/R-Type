#include "Button.hh"
#include "Debug.hh"

Button::Button(const std::string & text, const std::string& img, const Transformation & t, const Color & color, callback fptr, const std::string& id, IGraphicEngine* engine)
	: _engine(engine), _color(color), _text(text), _textureName(img), _fptr(fptr)
{
	_transformation = t;
	_id = id;
	_sprite = new Sprite(img, t, engine, color);
	_transformation.setBounds(_sprite->getTransformation().getWidth(), _sprite->getTransformation().getHeight());
}

Button::~Button()
{
	if (_sprite)
		delete _sprite;
}

bool Button::isPressed(uint32_t x, uint32_t y) const
{
	uint32_t mx = _transformation.getX();
	uint32_t my = _transformation.getY();
	uint32_t mwidth = _transformation.getWidth();
	uint32_t mheight = _transformation.getHeight();
	return (x >= mx && x <= (mx + mwidth) &&
		y >= my && y <= (my + mheight));
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
	_sprite->setTransformation(t);
	_transformation.setBounds(_sprite->getTransformation().getWidth(), _sprite->getTransformation().getHeight());

}

void Button::draw()
{
	if (_engine)
		_engine->drawSprite(*_sprite);
	else
		DEBUG_MSG("No instance of GraphicEngine");
}


const Sprite& Button::getSprite() const
{
	return (*_sprite);
}

void Button::onAction()
{
	if (_fptr != nullptr)
		_fptr();
}

void Button::onHover(uint32_t x, uint32_t y)
{
	if (isPressed(x, y)) {
		_sprite->setColor(Color::Darker);
	}
	else
		_sprite->setColor(Color::White);
}
