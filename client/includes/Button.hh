#ifndef BUTTON_H_
# define BUTTON_H_

# include "GraphicEngine.hh"
# include "ICallBack.hh"

class GraphicEngine;
class TextField;

class Button : public Drawable, public ICallback
{
public:
	Button(const std::string& text, const std::string& img, const Transformation& t, const Color& color, callback fptr, const std::string& id, IGraphicEngine* engine);
	virtual ~Button();

	// ICallback
	bool isPressed(uint32_t x, uint32_t y) const;
	void onAction();
	void onHover(uint32_t x, uint32_t y);
	const callback& getCallback() const;

	// Drawable
	virtual void draw();

	virtual const sf::Sprite& getSprite() const;
	const std::string& getName() const;
	const std::string& getTextureName() const;
	const Color& getColor() const;
	virtual void setTransformation(const Transformation& t);

private:
	GraphicEngine* _engine;
	Color _color;
	callback _fptr;
	sf::Sprite _sprite;

	std::string _text;
	std::string _textureName;
};

#endif /* BUTTON_H_ */