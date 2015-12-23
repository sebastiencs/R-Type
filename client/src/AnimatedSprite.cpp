#include <cstdlib>
#include "AnimatedSprite.hh"

AnimatedSprite::AnimatedSprite(const std::string& img, long fullAnimationTime, const Transformation& t, IGraphicEngine* engine, const Color& color)
	: Sprite(img, t), _nameSprite(img)
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
	_animationLength = fullAnimationTime;
	_timer = new Timer();
	_timer->start();
	_nbrStates = std::stoi(_nameSprite.substr(_nameSprite.find('-') + 1));
}

AnimatedSprite::~AnimatedSprite()
{
	if (_timer)
		delete _timer;
}

void AnimatedSprite::draw()
{
	_width = sprite.getTextureRect().width;// getTransformation().getWidth();
	_height = sprite.getTextureRect().height;//getTransformation().getHeight();
	if (_timer->ms() > _animationLength) {
		_states %= _nbrStates;
		++_states;
		_timer->reset();
	}
	_transformation.setCrop((_width / _nbrStates) * _states, 0, static_cast<uint16_t>((_width / _nbrStates)), _height);
	_transformation.setBounds(_width, _height);

	if (getTransformation().hasCrop())
	{
		_subRect.left = getTransformation().getCrop().at(Transformation::CROP::SRCX);
		_subRect.top = getTransformation().getCrop().at(Transformation::CROP::SRCY);
		_subRect.width = getTransformation().getCrop().at(Transformation::CROP::SRCWIDTH);
		_subRect.height = getTransformation().getCrop().at(Transformation::CROP::SRCHEIGHT);
	}
	else
	{
		_subRect.left = 0;
		_subRect.top = 0;
		_subRect.width = 0;
		_subRect.height = 0;
	}
	if (_visible && engine)
		engine->drawSprite(sprite);
}

void AnimatedSprite::setEngine(IGraphicEngine * engine)
{
	if ((this->engine = dynamic_cast<GraphicEngine*>(engine))) {
		sprite = sf::Sprite(this->engine->loadTexture(img), _subRect);
		transform(_transformation, color);
		_transformation.setBounds(static_cast<uint16_t>(sprite.getGlobalBounds().width), static_cast<uint16_t>(sprite.getGlobalBounds().height));
	}
	else
		throw std::runtime_error("Sprite: wrong GraphicEngine");
}
