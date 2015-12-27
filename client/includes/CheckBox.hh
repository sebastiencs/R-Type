#ifndef CHECK_BOX_H_
# define CHECK_BOX_H_

# include "ICallBack.hh"
# include "Drawable.hpp"
# include "Sprite.hh"

class GraphicEngine;
class TextField;

using IGraphicEngine_SharedPtr = std::shared_ptr<IGraphicEngine>;

class CheckBox : public Drawable, public ICallback
{
public:
	CheckBox(const std::string& text, const std::string& img, const Transformation& t, const Color& color, callback fptr, const std::string& id, IGraphicEngine_SharedPtr &engine);
	virtual ~CheckBox();

	// ICallback
	bool isPressed(const uint32_t x, const uint32_t y) const;
	bool onAction(const uint32_t x, const uint32_t y);
	void onHover(const uint32_t x, const uint32_t y);
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
	IGraphicEngine_SharedPtr& _engine;
	Color _color;
	callback _fptr;
	Sprite_UniquePtr _sprite;
	Sprite_UniquePtr _spriteCheck;

	std::string _text;
	std::string _textureName;
	bool _enabled;
	bool _check;
};

using CheckBox_SharedPtr = std::shared_ptr<CheckBox>;

#endif /* !CHECK_BOX_H_ */
