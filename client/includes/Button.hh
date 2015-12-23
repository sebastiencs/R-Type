#ifndef BUTTON_H_
# define BUTTON_H_

# include "ICallBack.hh"
# include "Drawable.hpp"
# include "Sprite.hh"

class GraphicEngine;
class TextField;

using IGraphicEngine_SharedPtr = std::shared_ptr<IGraphicEngine>;

class Button : public Drawable, public ICallback
{
public:
	Button(const std::string& text, const std::string& img, const Transformation& t, const Color& color, callback fptr, const std::string& id, IGraphicEngine_SharedPtr &engine);
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
	void setEnabled(bool enabled);

private:
	IGraphicEngine_SharedPtr &_engine;
	Color _color;
	callback _fptr;
	Sprite* _sprite;

	std::string _text;
	std::string _textureName;
  	bool _enabled;

};

using Button_SharedPtr = std::shared_ptr<Button>;

#endif /* !BUTTON_H_ */
