#include "TextField.hh"

TextField::TextField(const std::string & _text, const Transformation & t, uint16_t size, const std::string & font, const Color & color, const std::string& _id, GraphicEngine * engine)
{
	text = _text;
	id = _id;
	engine->drawText(_text, t, size, color, font);
}

TextField::~TextField()
{
}

const std::string& TextField::getId() const
{
	return id;
}
