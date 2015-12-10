#include "Text.hh"
#include "GraphicEngine.hh"

Text::Text(const std::string & text, const std::string & font, uint16_t size, const Transformation& t, IGraphicEngine * gengine, const Color& color) : color(color)
{
	this->font = font;
	textString = text;
	_size = size;
	_transformation = t;
	_visible = true;
	this->engine = nullptr;
	if (gengine) {
		engine = dynamic_cast<GraphicEngine*>(gengine);
		if (!engine)
			throw std::runtime_error("GraphicEngine is not set");
		this->text = sf::Text(text, engine->loadFont(font));
		this->text.setCharacterSize(size);
		transform(t, color);
	}

}

Text::Text(const Text& r) : _size(r._size), textString(r.textString), font(r.font), text(r.text), color(r.color), engine(r.engine) {
	_transformation = r._transformation;
	_visible = r._visible;
	if (engine) {
		this->text = sf::Text(textString, this->engine->loadFont(font));
		this->text.setCharacterSize(_size);
		transform(_transformation, color);
	}
}

void Text::draw()
{
	if (_visible && engine)
		engine->drawText(text);
}

void Text::setTransformation(const Transformation & t)
{
	_transformation = t;
	transform(t);
}

void Text::setEngine(IGraphicEngine * engine)
{
	if ((this->engine = dynamic_cast<GraphicEngine*>(engine))) {
		if (!this->engine)
			throw std::runtime_error("GraphicEngine is not set");
		this->text = sf::Text(this->textString, this->engine->loadFont(font));
		this->text.setCharacterSize(_size);
		transform(_transformation, color);
	}
}

void Text::setText(const std::string & txt)
{
	textString = txt;
	text.setString(txt);
	_transformation.setBounds(static_cast<uint16_t>(text.getGlobalBounds().width), static_cast<uint16_t>(text.getGlobalBounds().height));
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

	_transformation.setBounds(static_cast<uint16_t>(text.getGlobalBounds().width), static_cast<uint16_t>(text.getGlobalBounds().height));
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

bool Text::hasEngine() const
{
	return false;
}
