#ifndef BUTTON_H_
# define BUTTON_H_

# include "GraphicEngine.hh"
# include "ICallBack.hh"

class GraphicEngine;

class Button : public IDrawable, public ICallback
{
public:
	Button(const std::string& text, const std::string& img, const Transformation& t, const Color& color, callback fptr, const std::string& id, GraphicEngine* engine);
	virtual ~Button();

	// ICallback
	bool isPressed(uint32_t x, uint32_t y) const;
	void onAction();
	void onHover(uint32_t x, uint32_t y);
	const callback& getCallback() const;

	// IDrawable
	const std::string& getName() const;
	const std::string& getTextureName() const;
	const Transformation& getTransformation() const;
	const Color& getColor() const;
	const sf::Sprite& getSprite() const;
	const std::string& getId() const;

private:
	GraphicEngine* _engine;
	sf::Sprite _sprite;
	Color _color;
	std::string _id;
	Transformation _t;
	std::string _text;
	std::string _textureName;
	callback _fptr;
};

#endif /* BUTTON_H_ */