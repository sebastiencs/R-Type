#include "Patern.hh"

Patern::Patern()
{
	patern = nullptr;
}

Patern::Patern(const function & function) : patern(function)
{
}

Patern::~Patern()
{
}

void Patern::setPatern(const function & function)
{
	patern = function;
}

uint8_t Patern::applyPatern(uint8_t x)
{
	if (!patern)
		return patern(x);
	return x;
}

uint8_t absPatern(uint8_t x)
{
	return (uint8_t)std::abs(x);
}

uint8_t cosPatern(uint8_t x)
{
	return (uint8_t)std::cos(x);
}

uint8_t sinPatern(uint8_t x)
{
	return (uint8_t)std::sin(x);
}
