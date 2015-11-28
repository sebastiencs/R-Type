#ifndef BUTTON_H_
# define BUTTON_H_

# include "GraphicEngine.hh"
# include "ICallBack.hh"

class Button : public IDrawable, public ICallback
{
public:
	Button(const std::string& text, const std::string& img, const sf::Sprite& sprite, const Transformation& t,
		const Color& color, std::function<void()> fptr, void* arg = nullptr);
	virtual ~Button();

	// ICallback
	bool isPressed(uint32_t x, uint32_t y) const;
	void onAction(/*void *arg*/);
	void onHover(uint32_t x, uint32_t y);
	const void* getArgs() const;
	const std::function<void()>& getCallback() const;

	// IDrawable
	const std::string& getName() const;
	const std::string& getTextureName() const;
	const Transformation& getTransformation() const;
	const Color& getColor() const;
	const sf::Sprite& getSprite() const;

private:
	sf::Sprite _sprite;
	Color _color;
	Transformation _t;
	std::string _text;
	std::string _textureName;
	std::function<void()> _fptr;
	void* _arg;
};

#endif /* BUTTON_H_ */