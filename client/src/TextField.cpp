#include "TextField.hh"

TextField::TextField(const std::string & _text, const Transformation & _t, uint16_t _size, const std::string & _font, const Color & _color, const std::string& _id, IGraphicEngine * _engine) : color(_color)
{
	text = _text;
	id = _id;
	t = _t;
	size = _size;
	font = _font;
	engine = _engine;
}

TextField::~TextField()
{
}

const std::string& TextField::getId() const
{
	return id;
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

const Transformation & TextField::getTransformation() const
{
	return t;
}

Transformation & TextField::getTransformation()
{
	return t;
}

void TextField::draw()
{
	engine->drawText(text, t, size, color, font);
}

const std::string & TextField::getText() const
{
	return (text);
}

void TextField::setText(const std::string & txt)
{
	text = txt;
}
