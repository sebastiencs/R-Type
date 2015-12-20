#ifndef CHECK_BOX_H_
# define CHECK_BOX_H_

# include "ICallBack.hh"
# include "Drawable.hpp"
# include "Sprite.hh"

class GraphicEngine;
class TextField;

class CheckBox : public Drawable, public ICallback
{
public:
	CheckBox(const std::string& text, const std::string& img, const Transformation& t, const Color& color, callback fptr, const std::string& id, IGraphicEngine* engine);
	virtual ~CheckBox();

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
	const bool& getCheck() const;

	virtual void setTransformation(const Transformation& t);
	void setEnabled(bool enabled);
	void setCheck(bool check);

private:
	IGraphicEngine* _engine;
	Color _color;
	callback _fptr;
	Sprite* _sprite;
	Sprite* _spriteCheck;

	std::string _text;
	std::string _textureName;
	bool _enabled;
	bool _check;
};

#endif /* !CHECK_BOX_H_ */
