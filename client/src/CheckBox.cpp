#include "CheckBox.hh"
#include "Debug.hh"

CheckBox::CheckBox(const std::string & text, const std::string& img, const Transformation & t, const Color & color, callback fptr, const std::string& id, IGraphicEngine* engine)
	: _engine(engine), _color(color), _fptr(fptr), _text(text), _textureName(img), _enabled(true)
{
	_transformation = t;
	_id = id;
	_visible = true;
	_sprite = new Sprite(img, t, engine, color);
	_spriteCheck = new Sprite("CheckBoxCheck.png", t, engine, color);
	_transformation.setBounds(_sprite->getTransformation().getWidth(), _sprite->getTransformation().getHeight());
	_check = false;
}

CheckBox::~CheckBox()
{
	if (_sprite)
		delete _sprite;
}

bool CheckBox::isPressed(uint32_t x, uint32_t y) const
{
	uint32_t mx = _transformation.getX();
	uint32_t my = _transformation.getY();
	uint32_t mwidth = _transformation.getWidth();
	uint32_t mheight = _transformation.getHeight();
	return ((x >= mx && x <= (mx + mwidth) &&
		y >= my && y <= (my + mheight) && _visible && _enabled));
}

const std::string& CheckBox::getName() const
{
	return (_text);
}

const std::string & CheckBox::getTextureName() const
{
	return _textureName;
}

const callback& CheckBox::getCallback() const
{
	return _fptr;
}

const Color & CheckBox::getColor() const
{
	return (_color);
}

const bool & CheckBox::getCheck() const
{
	return _check;
}

void CheckBox::setTransformation(const Transformation & t)
{
	_transformation = t;
	_sprite->setTransformation(t);
	_spriteCheck->setTransformation(t);
	_transformation.setBounds(_sprite->getTransformation().getWidth(), _sprite->getTransformation().getHeight());
}

void CheckBox::setEnabled(bool enabled)
{
	_enabled = enabled;
}

void CheckBox::setCheck(bool check)
{
	_check = check;
}

void CheckBox::draw()
{
	if (_engine) {
		if (_visible)
		{
			if (_check)
				_engine->drawSprite(*_sprite);
			else
				_engine->drawSprite(*_spriteCheck);
		}
	}
	else
		DEBUG_MSG("No instance of GraphicEngine");
}


const Sprite& CheckBox::getSprite() const
{
	return (*_sprite);
}

bool CheckBox::onAction(uint32_t x, uint32_t y)
{
	if (_fptr && isPressed(x, y))
	{
		_check = (_check) ? false : true;
		_fptr();
		return true;
	}
	return false;
}

void CheckBox::onHover(uint32_t x, uint32_t y)
{
	if (isPressed(x, y)) {
		_sprite->setColor(Color::Darker);
		_spriteCheck->setColor(Color::Darker);
	}
	else if (!_enabled) {
		_sprite->setColor(Color::Darkest);
		_spriteCheck->setColor(Color::Darkest);
	}
	else
	{ 
		_sprite->setColor(Color::White);
		_spriteCheck->setColor(Color::White);
	}
}
