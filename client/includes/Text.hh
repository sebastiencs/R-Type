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
	Text(const std::string& text, const std::string& font, uint16_t size, const Transformation& t, IGraphicEngine* gengine = nullptr, const Color& color = Color::None);
	Text(const Text& r);
	~Text() {};

	// Drawable
	virtual void draw();
	virtual void setTransformation(const Transformation& t);

	void setEngine(IGraphicEngine* engine);
	void setText(const std::string& txt);
	void setColor(const Color& newColor);
	void transform(const Transformation& t, const Color& color = Color::None);

	const std::string& getText() const;
	uint32_t getSize() const;
	const Color& getColor() const;
	const std::string& getFont() const;

	bool hasEngine() const;
private:
	uint16_t _size;
	std::string textString;
	std::string font;
	sf::Text text;
	Color color;
	GraphicEngine* engine;
};
#endif /* !TEXT_HH_ */
