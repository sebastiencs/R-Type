#include "AnimatedSprite.hh"

AnimatedSprite::AnimatedSprite(const std::string & img, long interval, const Transformation & t, IGraphicEngine * engine, const Color & color)
	: _color(color), _nameSprite(img)
{
	_transformation = t;
	_id = img;
	_visible = true;

	_states = 0;
	_sprite = new Sprite(img, t, engine, color);
	_width = _sprite->getTransformation().getWidth();
	_height = _sprite->getTransformation().getHeight();
	_interval = interval;
	_timer = new Timer();
	_timer->start();
	_nbrStates = _nameSprite.substr(_nameSprite.find('-') + 1).size();
}

void AnimatedSprite::draw()
{
	if (_timer->ms(_interval)) {
		_states %= _nbrStates;
		_transformation.setCrop((_width / _nbrStates) * _states, 0, (_width / _nbrStates), _height);
		++_states;
		_timer->reset();
	}
	_engine->drawSplitImage(_nameSprite, _transformation, _color);
}
