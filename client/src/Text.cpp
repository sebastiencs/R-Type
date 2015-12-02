#include "Text.hh"
#include "GraphicEngine.hh"

Text::Text(const std::string & text, const std::string & font, uint16_t size, const Transformation& t, IGraphicEngine * gengine, const Color& color) : color(color)
{
	engine = dynamic_cast<GraphicEngine*>(gengine);
	if (!engine)
		throw std::runtime_error("GraphicEngine is not set");
	_transformation = t;
	this->font = font;
	this->text = sf::Text(text, engine->loadFont(font));
	this->text.setCharacterSize(size);
	textString = text;
	transform(t, color);
}

void Text::draw()
{
	engine->drawText(text);
}

void Text::setTransformation(const Transformation & t)
{
	_transformation = t;
	transform(t);
}

void Text::setText(const std::string & txt)
{
	textString = txt;
	text.setString(txt);
	_transformation.setBounds(text.getGlobalBounds().width, text.getGlobalBounds().height);
}

void Text::setColor(const Color & newColor)
{
	color = newColor;
	transform(_transformation, color);
}

void Text::transform(const Transformation & t, const Color & color)
{
	if (t.hasPosition())
		text.setPosition((float)t.getX(), (float)t.getY());
	if (t.hasRotation())
		text.rotate(t.getRotation());
	if (color.isUsed())
		text.setColor(sf::Color(color.getColor()));
	if (t.hasScale())
		text.setScale(t.getScaleX(), t.getScaleY());

	_transformation.setBounds(text.getGlobalBounds().width, text.getGlobalBounds().height);
}

const std::string & Text::getText() const
{
	return textString;
}

uint32_t Text::getSize() const
{
	return text.getCharacterSize();
}

const Color & Text::getColor() const
{
	return color;
}

const std::string & Text::getFont() const
{
	return font;
}
