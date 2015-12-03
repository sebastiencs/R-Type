#ifndef BUTTON_H_
# define BUTTON_H_

# include "ICallBack.hh"
# include "Drawable.hpp"
# include "Sprite.hh"

class GraphicEngine;
class TextField;

class Button : public Drawable, public ICallback
{
public:
	Button(const std::string& text, const std::string& img, const Transformation& t, const Color& color, callback fptr, const std::string& id, IGraphicEngine* engine);
	virtual ~Button();

	// ICallback
	bool isPressed(uint32_t x, uint32_t y) const;
	bool onAction(uint32_t x, uint32_t y);
	void onHover(uint32_t x, uint32_t y);
	const callback& getCallback() const;

	// Drawable
	virtual void draw();

	virtual const Sprite& getSprite() const;
	const std::string& getName() const;
	const std::string& getTextureName() const;
	const Color& getColor() const;
	virtual void setTransformation(const Transformation& t);

private:
	IGraphicEngine* _engine;
	Color _color;
	callback _fptr;
	Sprite* _sprite;

	std::string _text;
	std::string _textureName;
};

#endif /* !BUTTON_H_ */
