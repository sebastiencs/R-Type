# include "Transformation.hh"

Transformation::Transformation()
{
	_hasPos = false;
	_hasCrop = false;
	_hasRotation = false;
	_posX = 0;
	_posY = 0;
	_rotation = 0;
	crop[SRCX] = 0;
	crop[SRCY] = 0;
	crop[SRCWIDTH] = 0;
	crop[SRCHEIGHT] = 0;
}

Transformation::Transformation(uint16_t x, uint16_t y)
{
	setPosition(x, y);
	_hasCrop = false;
	_hasRotation = false;
	_rotation = 0;
	crop[SRCX] = 0;
	crop[SRCY] = 0;
	crop[SRCWIDTH] = 0;
	crop[SRCHEIGHT] = 0;
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

bool operator==(const Transformation& lhs, const Transformation& rhs) {
	return ((lhs.hasPosition() == rhs.hasPosition()) &&
		(lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY()) &&
		(lhs.hasRotation() == rhs.hasRotation()) &&
		(lhs.getRotation() == rhs.getRotation()) &&
		((lhs.hasCrop() == rhs.hasCrop()) &&
		(lhs.getCrop().at(Transformation::CROP::SRCX) == rhs.getCrop().at(Transformation::CROP::SRCX) &&
			lhs.getCrop().at(Transformation::CROP::SRCY) == rhs.getCrop().at(Transformation::CROP::SRCY) &&
			lhs.getCrop().at(Transformation::CROP::SRCWIDTH) == rhs.getCrop().at(Transformation::CROP::SRCWIDTH) &&
			lhs.getCrop().at(Transformation::CROP::SRCHEIGHT) == rhs.getCrop().at(Transformation::CROP::SRCHEIGHT))));
}
