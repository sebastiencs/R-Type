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
	Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255, bool used = true);

	uint32_t getColor() const;
	bool isUsed() const;

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