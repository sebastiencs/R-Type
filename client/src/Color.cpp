#include "Color.hh"

Color::Color(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha, bool used) :
	_r(red), _g(green), _b(blue), _a(alpha), _used(used)
{
}

uint32_t Color::getColor() const
{
	return RGBA(_r, _g, _b, _a);
}

bool Color::isUsed() const
{
	return _used;
}

const Color Color::Black = Color(0, 0, 0, 255);
const Color Color::White = Color(255, 255, 255, 255);
const Color Color::Red = Color(255, 0, 0, 255);
const Color Color::Green = Color(0, 255, 0, 255);
const Color Color::Blue = Color(0, 0, 255, 255);
const Color Color::Transparent = Color(0, 0, 0, 0);
const Color Color::None = Color(0, 0, 0, 0, false);
