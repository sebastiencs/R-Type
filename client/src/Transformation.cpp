# include "Transformation.hh"

Transformation::Transformation()
{
	_hasPos = false;
	_hasCrop = false;
	_hasRotation = false;
}

Transformation::Transformation(uint16_t x, uint16_t y)
{
	setPosition(x, y);
	_hasCrop = false;
	_hasRotation = false;
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
