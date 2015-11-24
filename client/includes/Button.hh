#ifndef BUTTON_H_
# define BUTTON_H_

# include "GraphicEngine.hh"
# include "ICallBack.hh"

class Button : public ICallBack
{
public:
	Button(const std::string& text, const sf::Sprite& sprite, std::function<void(void *)> fptr = nullptr);
	virtual ~Button();

	const bool isPressed(const int x, const int y) const;
	const std::string& getName() const;
	const sf::Sprite& getSprite() const;
	void onAction(void *arg);

private:
	sf::Sprite _sprite;
	std::string _text;
	std::function<void(void *)> _fptr;
};

#endif /* BUTTON_H_ */