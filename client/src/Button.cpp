#include "Button.hh"


Button::Button(const std::string & text, const std::string& img, const Transformation & t, const Color & color, callback fptr, const std::string& id, IGraphicEngine* engine)
  : _engine(dynamic_cast<GraphicEngine* >(engine)), _color(color), _id(id), _t(t), _text(text), _textureName(img), _fptr(fptr)
{
	if (_engine)
	{
		_sprite.setTexture(_engine->loadTexture(_textureName));
		_engine->transformSprite(_sprite, _t, _color);
	}
}

Button::~Button()
{
	//if (textField)
	//	delete textField;
}

bool Button::isPressed(uint32_t x, uint32_t y) const
{
	return (x >= _sprite.getPosition().x && x <= ((_sprite.getLocalBounds().width * _sprite.getScale().x) + _sprite.getPosition().x) &&
		y >= _sprite.getPosition().y && y <= ((_sprite.getLocalBounds().height * _sprite.getScale().y) + _sprite.getPosition().y));
}

const std::string& Button::getName() const
{
	return (_text);
}

const std::string & Button::getTextureName() const
{
	return _textureName;
}

const callback& Button::getCallback() const
{
	return _fptr;
}

const Transformation & Button::getTransformation() const
{
	return (_t);
}

const Color & Button::getColor() const
{
	return (_color);
}

void Button::centerText()
{
	//size_t CharacterSize = Text.GetCharacterSize();
	//sf::Font Font = Text.GetFont();
	//std::string String = Text.GetString().ToAnsiString();
	//bool bold = (Text.GetStyle() & sf::Text::Bold);
	//size_t MaxHeight = 0;

	//for (size_t x = 0; x<Text.GetString().GetSize(); ++x)
	//{
	//	sf::Uint32 Character = String.at(x);

	//	const sf::Glyph& CurrentGlyph = Font.GetGlyph(Character, CharacterSize, bold);

	//	size_t Height = CurrentGlyph.Bounds.Height;

	//	if (MaxHeight < Height)
	//		MaxHeight = Height;
	//}

	//sf::FloatRect rect = Text.GetRect();

	//rect.Left = (TextureNormal.GetWidth() / 2.0f) - (rect.Width / 2.0f);
	//rect.Top = (TextureNormal.GetHeight() / 2.0f) - (MaxHeight / 2.0f) - (rect.Height - MaxHeight) + ((rect.Height - CharacterSize) / 2.0f);

	//Text.SetPosition(rect.Left, rect.Top);
}

void Button::draw()
{
	if (_engine)
		_engine->drawSprite(_sprite);
	else
		DEBUG_MSG("No instance of GraphicEngine");
}

const std::string& Button::getId() const
{
	return _id;
}


const sf::Sprite& Button::getSprite() const
{
	return (_sprite);
}

void Button::onAction()
{
	if (_fptr != nullptr)
		_fptr();
}

void Button::onHover(uint32_t x, uint32_t y)
{
	if (isPressed(x, y)) {
		_sprite.setColor(sf::Color(Color::Darker.getColor()));
	}
	else
		_sprite.setColor(sf::Color::White);
}
