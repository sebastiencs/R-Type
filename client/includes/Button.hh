#ifndef BUTTON_H_
# define BUTTON_H_

# include "GraphicEngine.hh"
# include "ICallBack.hh"

class Button : public ICallBack
{
public:
	Button(const std::string& text, const std::string& img, const sf::Sprite& sprite, const Transformation& t,
		const Color& color, std::function<void(void *)> fptr, void* arg = nullptr);
	virtual ~Button();

	const bool isPressed(const int x, const int y) const;
	const std::string& getName() const;
	const std::string& getTextureName() const;
	const std::function<void(void *)>& getCallback() const;
	const void* getArgs() const;
	const Transformation& getTransformation() const;
	const Color& getColor() const;
	const sf::Sprite& getSprite() const;
	void onAction(void *arg);

private:
	sf::Sprite _sprite;
	Color _color;
	Transformation _t;
	std::string _text;
	std::string _textureName;
	std::function<void(void *)> _fptr;
	void* _arg;
};

#endif /* BUTTON_H_ */