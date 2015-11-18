#ifndef TRANSFORMATION_H_
# define TRANSFORMATION_H_

# include <iostream>
# include <vector>

class Transformation {
private:
	uint16_t _posX;
	uint16_t _posY;
	bool _hasPos;

	std::vector<uint16_t> crop;
	bool _hasCrop;

	uint16_t _rotation;
	bool _hasRotation;

public:
	Transformation();
	~Transformation();

	void setPosition(uint16_t x, uint16_t y);
	void setCrop(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
	void setRotation(uint16_t rotation);

	uint16_t getX() const;
	uint16_t getY() const;
	const std::vector<uint16_t>& getCrop() const;
	uint16_t getRotation() const;

	bool hasPosition() const;
	bool hasCrop() const;
	bool hasRotation() const;

	enum {
		SRCX = 0,
		SRCY,
		SRCWIDTH,
		SRCHEIGHT
	};
};

#endif /* !TRANSFORMATION_H_ */