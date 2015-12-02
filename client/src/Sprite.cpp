#include "Sprite.hh"

Sprite::Sprite(const std::string & img, const Transformation & t, IGraphicEngine * engine, const Color& color) : color(color)
{
	_transformation = t;
	_id = img;
	this->img = img;
	this->engine = dynamic_cast<GraphicEngine* >(engine);
	if (!engine)
		throw std::runtime_error("GraphicEngine not set");
	sprite = sf::Sprite(this->engine->loadTexture(img));
	transform(_transformation, color);
	_transformation.setBounds(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}

void Sprite::setTransformation(const Transformation & t)
{
	_transformation = t;
	transform(t, color);
}

void Sprite::draw()
{
	engine->drawSprite(sprite);
}

void Sprite::setColor(const Color & newColor)
{
	color = newColor;
	transform(_transformation, color);
}

void Sprite::transform(const Transformation & t, const Color & color)
{
	if (t.hasPosition())
		sprite.setPosition((float)t.getX(), (float)t.getY());
	if (t.hasRotation())
		sprite.rotate(t.getRotation());
	if (color.isUsed())
		sprite.setColor(sf::Color(color.getColor()));
	if (t.hasScale())
		sprite.setScale(t.getScaleX(), t.getScaleY());

	_transformation.setBounds(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}

const std::string & Sprite::getImage() const
{
	return img;
}

const Color & Sprite::getColor() const
{
	return color;
}
