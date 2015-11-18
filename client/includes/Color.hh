#ifndef COLOR_H_
# define COLOR_H_

# include <iostream>
# include <map>

# define RGBA(r,g,b,a) ((((a)&0xFF)<<24) | (((b)&0xFF)<<16) | (((g)&0xFF)<<8) | (((r)&0xFF)<<0))

class Color {
private:
	uint32_t _r;
	uint32_t _g;
	uint32_t _b;
	uint32_t _a;
	bool _used;
public:
	Color(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha = 255, bool used = true);

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

#endif /* !COLOR_H_ */