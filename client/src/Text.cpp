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
  // Cette ligne me fait:
  // CMakeFiles/Client.dir/client/src/Text.cpp.o: dans la fonction « Text::getText() const »:
  // /home/sebastien/travaux/R-Type/build/../client/src/Text.cpp:55: référence indéfinie vers « sf::String::operator std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >() const »

//	return text.getString();
  return nullptr;
}

uint32_t Text::getSize() const
{
	text.getCharacterSize();
}

const Color & Text::getColor() const
{
	return color;
}

const std::string & Text::getFont() const
{
	return font;
}
