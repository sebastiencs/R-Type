#ifndef COLOR_H_
# define COLOR_H_

#include <iostream>
#include <map>

class Color {
private:
	uint8_t _r;
	uint8_t _g;
	uint8_t _b;
	uint8_t _a;
public:
	Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);

	uint32_t getColor() const;
};
#endif /* !COLOR_H_ */