#ifndef COLOR_H_
# define COLOR_H_

# include <iostream>
# include <map>

# define RGBA(r,g,b,a) ((((r)&0xFF)<<24) | (((g)&0xFF)<<16) | (((b)&0xFF)<<8) | (((a)&0xFF)<<0))

class Color {
private:
	uint8_t _r;
	uint8_t _g;
	uint8_t _b;
	uint8_t _a;
	bool _used;
public:
	Color(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha = 255, const bool used = true);

	uint32_t getColor() const;
	bool isUsed() const;

	static const Color Darker;
	static const Color Darkest;
	static const Color Black;
	static const Color White;
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Transparent;
	static const Color None;
};

bool operator==(const Color& lhs, const Color& rhs);

#endif /* !COLOR_H_ */
