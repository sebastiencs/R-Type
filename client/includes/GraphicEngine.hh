#ifndef GRAPHIC_ENGINE_H_
# define GRAPHIC_ENGINE_H_

# include <thread>
# include <iostream>
# include <chrono>
# include <map>
# include <list>
# include <exception>
# include <SFML/Window/Window.hpp>
# include <SFML/Graphics/RenderWindow.hpp>
# include <SFML/Window/Event.hpp>
# include <SFML/Graphics/Image.hpp>
# include <SFML/Graphics/Font.hpp>
# include <SFML/Graphics/Text.hpp>
# include <SFML/Graphics/Texture.hpp>
# include <SFML/Graphics/Sprite.hpp>
# include <SFML/System/Time.hpp>
# include "IGraphicEngine.hh"
# include "Timer.hh"
# include "Debug.hh"

class Button;
class Drawable;
class Text;
class Sprite;
class ICallback;
class IDrawable;

enum KeyAlias {
	UP = 0,
	RIGHT,
	DOWN,
	LEFT,
	SPACEE
};

using RenderWindow_UniquePtr = std::shared_ptr<sf::RenderWindow>;
using Texture_SharedPtr = std::shared_ptr<sf::Texture>;
using Font_SharedPtr = std::shared_ptr<sf::Font>;

class GraphicEngine : public IGraphicEngine {

public:
	GraphicEngine();
	virtual ~GraphicEngine();

	virtual void createWindow(const uint16_t sizeX, const uint16_t sizeY, const std::string& title);

	virtual void drawImage(const std::string& name, const Transformation& transformation, const Color& color = Color::None);
	virtual void drawSplitImage(const std::string& name, const Transformation& transformation, const Color& color);
	virtual void drawSplitImage(Sprite& sprite);
	virtual void drawSprite(Sprite& sprite);
	void drawSprite(const sf::Sprite& sprite);

	virtual void drawText(Text& text);
	void drawText(const sf::Text& text);
	virtual void drawText(const std::string& text, const Transformation& transformation,
		uint16_t size, const Color& color = Color::White, const std::string& font = "");

	virtual void handleEvents();
	void handleMovements();
	virtual void launch();
	virtual void setCallbackFunction(callback, void* arg);
	virtual void setMouseClickCallback(mouseCallback);
	virtual void setMouseMovedCallback(mouseCallback);
	virtual void setTextEnteredCallback(textEnteredCallback);
	virtual void setUsableKeyPressedCallback(usableKeyPressedCallback);

	virtual textEnteredCallback getTextEnteredCallback() const;
	virtual int getWindowWidth() const;
	virtual int getWindowHeight() const;

	const sf::Texture& loadTexture(const std::string& img);
	const sf::Font& loadFont(const std::string& font);
	void transformSprite(sf::Sprite&, const Transformation&, const Color& color = Color::None);
	void transformSprite(sf::Text&, const Transformation&, const Color& color = Color::None);

	virtual void closeWindow();

	static int32_t getDeltaTimeMS();
	static float getDeltaTimeS();

	virtual void setInputMode(const InputMode mode);

	static const sf::Texture* None;
	static const sf::Font* NoneFont;

protected:
	bool loadImageFromFile(const std::string& file);
	bool loadFontFromFile(const std::string& file);

	ITimer_UniquePtr _timer;
	static sf::Time elapsedTime;
	callback call;
	textEnteredCallback _textEnteredcallback;
	mouseCallback _mouseClickCall;
	mouseCallback _mouseMoveCall;
	usableKeyPressedCallback _usableKeyPressedCallback;
	int windowWidth;
	int windowHeight;
	void* callbackArg;

	std::map<KeyAlias, sf::Keyboard::Key> keyMap;
	RenderWindow_UniquePtr window;
	std::list<ICallback *> elements;
	std::list<IDrawable *> dElements;
	std::map<std::string, Texture_SharedPtr> cachedImages;
	std::map<std::string, Font_SharedPtr> cachedFonts;
	std::map<uint8_t, std::string> shotTypeToSpriteString;
};


#endif /*! GRAPHIC_ENGINE_H_ */
