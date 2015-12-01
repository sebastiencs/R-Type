#ifndef TEXTFIELD_HH
# define TEXTFIELD_HH

# include "Transformation.hh"
# include "Color.hh"
# include "GraphicEngine.hh"

class GraphicEngine;

class TextField : public Drawable {
public:
	TextField(const std::string& _text, const Transformation& _t, uint16_t _size, const std::string& _font, const Color& _color, const std::string& _id, IGraphicEngine *_engine);
	virtual ~TextField();

	//Drawable
	virtual const sf::Sprite& getSprite() const;
	virtual Color& getColor();
	virtual void draw();

	const std::string& getText() const;
	void setText(const std::string& txt);

private:
	std::string text;
	std::string id;
	uint16_t size;
	Transformation t;
	std::string font;
	Color color;
	IGraphicEngine *engine;
};

#endif
