#ifndef TEXT_HH_
# define TEXT_HH_

# include <SFML/Graphics/Text.hpp>
//# include "GraphicEngine.hh"
# include "Drawable.hpp"
# include "Color.hh"

class IGraphicEngine;
class GraphicEngine;

class Text : public Drawable {
public:
	Text(const std::string& text, const std::string& font, uint16_t size, const Transformation& t, IGraphicEngine* gengine, const Color& color = Color::None);

	// Drawable
	virtual void draw();
	virtual void setTransformation(const Transformation& t);

	void setText(const std::string& txt);
	void setColor(const Color& newColor);
	void transform(const Transformation& t, const Color& color = Color::None);

	const std::string& getText() const;
	uint32_t getSize() const;
	const Color& getColor() const;
	const std::string& getFont() const;
private:
	std::string font;
	sf::Text text;
	Color color;
	GraphicEngine* engine;
};
#endif /* !TEXT_HH_ */
