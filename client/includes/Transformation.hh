#ifndef TRANSFORMATION_H_
# define TRANSFORMATION_H_

# include <iostream>
# include <vector>
# include <map>

class Transformation {
public:
	enum CROP {
		SRCX = 0,
		SRCY,
		SRCWIDTH,
		SRCHEIGHT
	};

	Transformation();
	Transformation(uint16_t x, uint16_t y);
	Transformation(const Transformation& t);
	Transformation& operator=(const Transformation& t);
	~Transformation();

	void setPosition(uint16_t x, uint16_t y);
	void setCrop(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
	void setRotation(uint16_t rotation);
	void setScale(float x, float y);
	void setBounds(uint16_t width, uint16_t height);

	uint16_t getX() const;
	uint16_t getY() const;
	const std::map<uint8_t, uint16_t>& getCrop() const;
	uint16_t getRotation() const;
	float getScaleX() const;
	float getScaleY() const;
	uint16_t getWidth() const;
	uint16_t getHeight() const;

	bool hasPosition() const;
	bool hasCrop() const;
	bool hasRotation() const;
	bool hasScale() const;
	bool hasBounds() const;

private:
	uint16_t _posX;
	uint16_t _posY;
	bool _hasPos;

	std::map<uint8_t, uint16_t> crop;
	bool _hasCrop;

	uint16_t _rotation;
	bool _hasRotation;

	float _scaleX;
	float _scaleY;
	bool _hasScale;

	uint16_t _width;
	uint16_t _height;
	bool _hasBounds;
};

bool operator==(const Transformation& lhs, const Transformation& rhs);

#endif /* !TRANSFORMATION_H_ */