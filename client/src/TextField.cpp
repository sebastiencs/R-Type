#include "TextField.hh"
#include "Text.hh"
#include "IGraphicEngine.hh"

TextField::TextField(const std::string & _text, const Transformation & t, uint16_t _size, const std::string & _font, const Color & _color, const std::string& id, IGraphicEngine * _engine) : color(_color)
{
	_id = id;
	_transformation = t;
	size = _size;
	font = _font;
	engine = _engine;
	//sfText = new sf::Text(text, _engine->loadFont(font));
	//sfText->setString(_text);
	//sfText->setCharacterSize(_size);
	//engine->transformSprite(*sfText, _transformation, color);

	// text = Text(_text, _font, _size, t, _engine, color);
	// _transformation.setBounds(text.getTransformation().getWidth(), text.getTransformation().getHeight());
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
//	engine->drawText(text);
}

void TextField::setTransformation(const Transformation & t)
{
	// _transformation = t;
	// text.setTransformation(t);
	// _transformation.setBounds(text.getTransformation().getWidth(), text.getTransformation().getHeight());
}

const std::string & TextField::getText() const
{
	// return (text.getText());
}

void TextField::setText(const std::string & txt)
{
	// text.setText(txt);
	// _transformation.setBounds(text.getTransformation().getWidth(), text.getTransformation().getHeight());
}
