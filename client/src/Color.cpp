#include "Color.hh"

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) :
	_r(red), _g(green), _b(blue), _a(alpha)
{
}

uint32_t Color::getColor() const
{
	return (_r * 1000000000) + (_g * 1000000) + (_b * 1000) + _a;
}
