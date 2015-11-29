#ifndef TEXTFIELD_HH
#define TEXTFIELD_HH

#include "Transformation.hh"
#include "Color.hh"
#include "GraphicEngine.hh"
#include "IDrawable.hh"

class GraphicEngine;

class TextField : public IDrawable {
public:
	TextField(const std::string& _text, const Transformation& _t, uint16_t _size, const std::string& _font, const Color& _color, const std::string& _id, IGraphicEngine *_engine);
	virtual ~TextField();

	//IDrawable
	virtual const std::string& getId() const;
	virtual const sf::Sprite& getSprite() const;
	virtual bool getVisible() const;
	virtual void setVisible(bool visible);
	virtual void draw();

private:
	bool _visible;
	std::string text;
	std::string id;
	uint16_t size;
	Transformation t;
	std::string font;
	Color color;
	IGraphicEngine *engine;
};

#endif
