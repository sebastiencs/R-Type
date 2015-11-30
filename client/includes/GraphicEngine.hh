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
# include "IGraphicEngine.hh"
# include "ICallBack.hh"
# include "IDrawable.hh"
# include "Paquets.hh"
# include "Packager.hh"
# include "Button.hh"
# include "Timer.hh"
# include "TextField.hh"

# define RS_PATH "ressources/"
# define FONT_PATH "ressources/fonts/"
# define DEFAULT_FONT "default.ttf"
# define DEFAULT_FONT_SIZE 12
# define MS_REFRESH 33

class Button;
class IDrawable;

class GraphicEngine : public IGraphicEngine {

public:
	GraphicEngine(Packager* packager);
	~GraphicEngine();

	virtual void createWindow(uint16_t sizeX, uint16_t sizeY, const std::string& title);

	virtual void drawImage(const std::string& name, const Transformation& transformation, const Color& color = Color::None);
	virtual void drawSplitImage(const std::string& name, const Transformation& transformation, const Color& color);
	void drawSprite(const sf::Sprite& sprite);

	virtual void drawText(const std::string& text, const Transformation& transformation,
		uint16_t size, const Color& color = Color::White, const std::string& font = "");

	virtual void handleEvents();
	virtual void launch();
	virtual void setCallbackFunction(callback, void* arg);
	virtual void setMouseClickCallback(mouseCallback);
	virtual void setMouseMovedCallback(mouseCallback);
	virtual void setTextEnteredCallback(textEnteredCallback);


	virtual int getWindowWidth() const;
	virtual int getWindowHeight() const;

	const sf::Texture& loadTexture(const std::string& img);
	void transformSprite(sf::Sprite&, const Transformation&, const Color& color = Color::None);
	void transformSprite(sf::Text&, const Transformation&, const Color& color = Color::None);

	virtual void closeWindow();

	static const sf::Texture* None;

protected:
	bool loadImageFromFile(const std::string& file);
	bool loadFontFromFile(const std::string& file);

	Packager* _packager;
	ITimer* _timer;
	callback call;
	textEnteredCallback _textEnteredcallback;
	mouseCallback _mouseClickCall;
	mouseCallback _mouseMoveCall;
	int windowWidth;
	int windowHeight;
	void* callbackArg;

	sf::RenderWindow* window;
	std::list<ICallback *> elements;
	std::list<IDrawable *> dElements;
	std::map<std::string, sf::Texture*> cachedImages;
	std::map<std::string, sf::Font*> cachedFonts;
	std::map<uint8_t, std::string> obstacleTypeToSpriteString;
	std::map<uint8_t, std::string> playerIDToSpriteString;
	std::map<uint8_t, std::string> shotTypeToSpriteString;
};


#endif /*! GRAPHIC_ENGINE_H_ */
