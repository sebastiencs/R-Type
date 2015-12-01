# include "Transformation.hh"

Transformation::Transformation()
{
	_hasPos = false;
	_hasCrop = false;
	_hasRotation = false;
	_hasScale = false;
	_hasBounds = false;
	_posX = 0;
	_posY = 0;
	_rotation = 0;
	crop[SRCX] = 0;
	crop[SRCY] = 0;
	crop[SRCWIDTH] = 0;
	crop[SRCHEIGHT] = 0;
	_scaleX = 1;
	_scaleY = 1;
	_width = 0;
	_height = 0;
}

Transformation::Transformation(uint16_t x, uint16_t y)
{
	setPosition(x, y);
	_hasCrop = false;
	_hasRotation = false;
	_hasScale = false;
	_hasBounds = false;
	_rotation = 0;
	crop[SRCX] = 0;
	crop[SRCY] = 0;
	crop[SRCWIDTH] = 0;
	crop[SRCHEIGHT] = 0;
	_scaleX = 1;
	_scaleY = 1;
	_width = 0;
	_height = 0;
}

Transformation::~Transformation()
{
}

void Transformation::setPosition(uint16_t x, uint16_t y)
{
	_hasPos = true;
	_posX = x;
	_posY = y;
}

void Transformation::setCrop(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
	_hasCrop = true;
	crop[SRCX] = x;
	crop[SRCY] = y;
	crop[SRCWIDTH] = width;
	crop[SRCHEIGHT] = height;
}

void Transformation::setRotation(uint16_t rotation)
{
	_hasRotation = true;
	_rotation = rotation;
}

void Transformation::setScale(float x, float y)
{
	_scaleX = x;
	_scaleY = y;
	_hasScale = true;
}

void Transformation::setBounds(uint16_t width, uint16_t height)
{
	_hasBounds = true;
	_width = width;
	_height = height;
}

uint16_t Transformation::getX() const
{
	return _posX;
}

uint16_t Transformation::getY() const
{
	return _posY;
}

const std::map<uint8_t, uint16_t>& Transformation::getCrop() const
{
	return crop;
}

uint16_t Transformation::getRotation() const
{
	return _rotation;
}

float Transformation::getScaleX() const
{
	return _scaleX;
}

float Transformation::getScaleY() const
{
	return _scaleY;
}

uint16_t Transformation::getWidth() const
{
	return _width;
}

uint16_t Transformation::getHeight() const
{
	return _height;
}

bool Transformation::hasPosition() const
{
	return _hasPos;
}

bool Transformation::hasCrop() const
{
	return _hasCrop;
}

bool Transformation::hasRotation() const
{
	return _hasRotation;
}

bool Transformation::hasScale() const
{
	return _hasScale;
}

bool Transformation::hasBounds() const
{
	return _hasBounds;
}

bool operator==(const Transformation& lhs, const Transformation& rhs) {
	return ((lhs.hasPosition() == rhs.hasPosition()) &&
		(lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY()) &&
		(lhs.hasRotation() == rhs.hasRotation()) &&
		(lhs.getRotation() == rhs.getRotation()) &&
		((lhs.hasCrop() == rhs.hasCrop()) &&
		(lhs.getCrop().at(Transformation::CROP::SRCX) == rhs.getCrop().at(Transformation::CROP::SRCX) &&
			lhs.getCrop().at(Transformation::CROP::SRCY) == rhs.getCrop().at(Transformation::CROP::SRCY) &&
			lhs.getCrop().at(Transformation::CROP::SRCWIDTH) == rhs.getCrop().at(Transformation::CROP::SRCWIDTH) &&
			lhs.getCrop().at(Transformation::CROP::SRCHEIGHT) == rhs.getCrop().at(Transformation::CROP::SRCHEIGHT))) &&
		lhs.hasBounds() == rhs.hasBounds() &&
		(lhs.getWidth() == rhs.getWidth() && lhs.getHeight() == rhs.getHeight()));
}
