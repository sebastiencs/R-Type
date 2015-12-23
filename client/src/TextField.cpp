#include "TextField.hh"
#include "Text.hh"
#include "IGraphicEngine.hh"

TextField::TextField(const std::string & _text, const Transformation & t, uint16_t _size, const std::string & _font, const Color & _color, const std::string& id, IGraphicEngine_SharedPtr &_eng) : engine(_eng), color(_color)
{
	_id = id;
	_transformation = t;
	_visible = true;

	size = _size;
	font = _font;
	text = std::make_unique<Text>(_text, _font, _size, t, std::move(_eng), color);
	_transformation.setBounds(text->getTransformation().getWidth(), text->getTransformation().getHeight());
}

TextField::~TextField()
{
}

Color & TextField::getColor()
{
	return color;
}

void TextField::draw()
{
	if (_visible)
		engine->drawText(*text);
}

void TextField::setTransformation(const Transformation & t)
{
	_transformation = t;
	text->setTransformation(t);
	_transformation.setBounds(text->getTransformation().getWidth(), text->getTransformation().getHeight());
}

void TextField::setColor(const Color& c)
{
	color = c;
	text->setColor(c);
}

const std::string & TextField::getText() const
{
	return (text->getText());
}

void TextField::setText(const std::string & txt)
{
	text->setText(txt);
	_transformation.setBounds(text->getTransformation().getWidth(), text->getTransformation().getHeight());
}
