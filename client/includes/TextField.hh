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
	virtual void draw();

	Color& getColor();
	const std::string& getText() const;
	void setText(const std::string& txt);

private:
	IGraphicEngine *engine;
	Color color;
	uint16_t size;

	std::string font;
	std::string text;
};

#endif /* !TEXTFIELD_HH */
