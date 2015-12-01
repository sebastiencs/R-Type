#include "TextField.hh"

TextField::TextField(const std::string & _text, const Transformation & t, uint16_t _size, const std::string & _font, const Color & _color, const std::string& id, IGraphicEngine * _engine) : color(_color)
{
	text = _text;
	_id = id;
	_transformation = t;
	size = _size;
	font = _font;
	engine = _engine;
}

TextField::~TextField()
{
}


const sf::Sprite & TextField::getSprite() const
{
	sf::Sprite *sprite = new sf::Sprite();
	return *sprite;
}

Color & TextField::getColor()
{
	return color;
}

void TextField::draw()
{
	engine->drawText(text, _transformation, size, color, font);
}

const std::string & TextField::getText() const
{
	return (text);
}

void TextField::setText(const std::string & txt)
{
	text = txt;
}
