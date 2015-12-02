#ifndef TEXTFIELD_HH
# define TEXTFIELD_HH

# include "Transformation.hh"
# include "Color.hh"
# include "GraphicEngine.hh"
# include "Drawable.hpp"
//# include "Text.hh"

class GraphicEngine;
class Text;

class TextField : public Drawable {
public:
	TextField(const std::string& _text, const Transformation& _t, uint16_t _size, const std::string& _font, const Color& _color, const std::string& _id, IGraphicEngine *_engine);
	virtual ~TextField();

	//Drawable
	virtual void draw();
	virtual void setTransformation(const Transformation& t);
	virtual void setColor(const Color& c);

	Color& getColor();
	const std::string& getText() const;
	void setText(const std::string& txt);

private:
	IGraphicEngine *engine;
	Text *text;
	Color color;
	uint16_t size;

	std::string font;
};

#endif /* !TEXTFIELD_HH */
