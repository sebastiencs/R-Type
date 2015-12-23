#ifndef TEXTFIELD_HH
# define TEXTFIELD_HH

# include "Transformation.hh"
# include "Color.hh"
# include "GraphicEngine.hh"
# include "Drawable.hpp"

class GraphicEngine;
class Text;

using Text_UniquePtr = std::unique_ptr<Text>;

class TextField : public Drawable {
public:
	TextField(const std::string& _text, const Transformation& _t, uint16_t _size, const std::string& _font, const Color& _color, const std::string& _id, IGraphicEngine_SharedPtr &_engine);
	virtual ~TextField();

	virtual void draw();
	virtual void setTransformation(const Transformation& t);
	virtual void setColor(const Color& c);

	Color& getColor();
	const std::string& getText() const;
	void setText(const std::string& txt);

private:
	IGraphicEngine_SharedPtr &engine;
	Text_UniquePtr text;
	Color color;
	uint16_t size;

	std::string font;
};

using TextField_SharedPtr = std::shared_ptr<TextField>;

#endif /* !TEXTFIELD_HH */
