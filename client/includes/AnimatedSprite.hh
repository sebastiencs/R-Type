#ifndef ANIMATED_SPRITE_HH_
# define ANIMATED_SPRITE_HH_

# include "Drawable.hpp"
# include "Sprite.hh"
# include "Timer.hh"

class IGraphicEngine;
class GraphicEngine;

class AnimatedSprite : public Drawable {
public:
	AnimatedSprite(const std::string& img, long interval, const Transformation& t, IGraphicEngine* engine, const Color& color = Color::None);

	// Drawable
	virtual void draw();

protected:
	IGraphicEngine* _engine;
	Timer *_timer;
	Sprite *_sprite;
	Color _color;

	uint16_t _width;
	uint16_t _height;
	size_t _nbrStates;
	uint8_t _states;
	long _interval;
	std::string _nameSprite;
};
#endif /* !ANIMATED_SPRITE_HH_ */