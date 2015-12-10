#include <cstdlib>
#include "AnimatedSprite.hh"

AnimatedSprite::AnimatedSprite(const std::string & img, long interval, const Transformation & t, IGraphicEngine * engine, const Color & color)
	: _color(color), _nameSprite(img), _engine(engine), Sprite(img, t)
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
	_nbrStates = std::stoi(_nameSprite.substr(_nameSprite.find('-') + 1).c_str());
}

void AnimatedSprite::draw()
{
	if (_timer->ms() > _interval) {
		_states %= _nbrStates;
		++_states;
		_timer->reset();
	}
	_transformation.setCrop((_width / _nbrStates) * _states, 0, (_width / _nbrStates), _height);
	_engine->drawSplitImage(_nameSprite, _transformation, _color);
}
