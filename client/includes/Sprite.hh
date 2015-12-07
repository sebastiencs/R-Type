#ifndef SPRITE_HH_
# define SPRITE_HH_

# include <SFML/Graphics/Sprite.hpp>
# include "GraphicEngine.hh"
# include "Drawable.hpp"
# include "Color.hh"

class IGraphicEngine;
class GraphicEngine;

class Sprite : public Drawable {
public:
	Sprite(const std::string& img, const Transformation& t, IGraphicEngine* engine, const Color& color = Color::None);

	// Drawable
	virtual void setTransformation(const Transformation& t);
	virtual void draw();

	void setColor(const Color& newColor);
	void transform(const Transformation& t, const Color& color = Color::None);

	const std::string& getImage() const;
	const Color& getColor() const;

	bool isPressed(uint32_t x, uint32_t y);

protected:
	sf::Sprite sprite;
	std::string img;
	GraphicEngine* engine;
	Color color;
};
#endif /* !SPRITE_HH_ */