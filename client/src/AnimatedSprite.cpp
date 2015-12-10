#include <cstdlib>
#include "AnimatedSprite.hh"

AnimatedSprite::AnimatedSprite(const std::string& img, long interval, const Transformation& t, IGraphicEngine* engine, const Color& color)
	: _nameSprite(img), Sprite(img, t)
{
	_transformation = t;
	_id = img;
	_visible = true;
	this->color = color;
	this->engine = nullptr;
	if (engine) {
		this->engine = dynamic_cast<GraphicEngine*>(engine);
		if (!engine)
			throw std::runtime_error("GraphicEngine not set");
	}
	_states = 0;
	_width = getTransformation().getWidth();
	_height = getTransformation().getHeight();
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
	_transformation.setBounds(_width, _height);
	if (_visible && engine)
		engine->drawSplitImage(_nameSprite, _transformation, color);
	else
		std::cout << "FOIOFPAIOPFJAFJAPOFJ";
}
