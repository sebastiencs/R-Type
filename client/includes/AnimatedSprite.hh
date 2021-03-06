#ifndef ANIMATED_SPRITE_HH_
# define ANIMATED_SPRITE_HH_

# include "Sprite.hh"
# include "Timer.hh"

class IGraphicEngine;
class GraphicEngine;

class AnimatedSprite : public Sprite {
public:
	AnimatedSprite(const std::string& img, const long, const Transformation& t, IGraphicEngine* engine = nullptr, const Color& color = Color::None);
	virtual ~AnimatedSprite();
	// Drawable
	virtual void setEngine(IGraphicEngine * engine);
	virtual void draw();

protected:
	ITimer_SharedPtr _timer;
	sf::IntRect _subRect;

	uint16_t _width;
	uint16_t _height;
	size_t _nbrStates;
	uint8_t _states;
	long _animationLength;
	std::string _nameSprite;
};
#endif /* !ANIMATED_SPRITE_HH_ */
