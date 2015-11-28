#ifndef BUTTON_H_
# define BUTTON_H_

# include "GraphicEngine.hh"
# include "ICallBack.hh"

class Button : public IDrawable, public ICallback
{
public:
	Button(const std::string& text, const std::string& img, const sf::Sprite& sprite, const Transformation& t, const Color& color, std::function<void()> fptr, uint32_t id);
	virtual ~Button();

	// ICallback
	bool isPressed(uint32_t x, uint32_t y) const;
	void onAction();
	void onHover(uint32_t x, uint32_t y);
	const std::function<void()>& getCallback() const;

	// IDrawable
	const std::string& getName() const;
	const std::string& getTextureName() const;
	const Transformation& getTransformation() const;
	const Color& getColor() const;
	const sf::Sprite& getSprite() const;


	const int getId() const;
private:
	sf::Sprite _sprite;
	Color _color;
	uint32_t _id;
	Transformation _t;
	std::string _text;
	std::string _textureName;
	std::function<void()> _fptr;
};

#endif /* BUTTON_H_ */