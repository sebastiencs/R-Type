#ifndef TEXTFIELD_HH
#define TEXTFIELD_HH

#include "Transformation.hh"
#include "Color.hh"
#include "GraphicEngine.hh"

class GraphicEngine;

class TextField : public IDrawable {
public:
	TextField(const std::string& _text, const Transformation& t, uint16_t size, const std::string& font, const Color& color, const std::string& _id, GraphicEngine *engine);
	virtual ~TextField();

	virtual const std::string& getId() const;
private:
	std::string text;
	std::string id;
};

#endif