#ifndef GRAPHIC_ENGINE_H_
# define GRAPHIC_ENGINE_H_

# include <thread>
# include <iostream>
# include <chrono>
# include <map>
# include <list>
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

# define RS_PATH "ressources/"
# define FONT_PATH "ressources/fonts/"
# define DEFAULT_FONT "default.ttf"
# define DEFAULT_FONT_SIZE 12
# define MS_REFRESH 33.3

class Button;
class IDrawable;

class GraphicEngine : public IGraphicEngine {

public:
	GraphicEngine(Packager* packager);
	~GraphicEngine();

	virtual void createWindow(uint16_t sizeX, uint16_t sizeY, const std::string& title);
	virtual void displayButton(const std::string& txt, const std::string & img, const Transformation & t, const Color & color, callback fptr = nullptr, void* arg = nullptr);
	virtual void eraseButton(const std::string& txt);

	virtual void drawImage(const std::string& name, const Transformation& transformation, const Color& color = Color::None);
	virtual void drawSplitImage(const std::string& name, const Transformation& transformation, const Color& color);
	virtual void drawText(const std::string& text, const Transformation& transformation,
		uint16_t size, const Color& color = Color::White, const std::string& font = "");

	virtual void handleEvents();
	virtual void repaint();
	virtual void launch();
	virtual void setCallbackFunction(std::function<void(void *)>, void* arg);

	virtual int getWindowWidth() const;
	virtual int getWindowHeight() const;

protected:
	bool loadImageFromFile(const std::string& file);
	bool loadFontFromFile(const std::string& file);

	Packager* _packager;
	Timer _timer;
	//callback call;
	std::function<void(void *)> call;
	int windowWidth;
	int windowHeight;
	void* callbackArg;

	sf::RenderWindow* window;
	std::list<ICallback *> elements;
	std::map<std::string, sf::Texture*> cachedImages;
	std::map<std::string, sf::Font*> cachedFonts;
	std::map<uint8_t, std::string> obstacleTypeToSpriteString;
	std::map<uint8_t, std::string> playerIDToSpriteString;
	std::map<uint8_t, std::string> shotTypeToSpriteString;
};


#endif /*! GRAPHIC_ENGINE_H_ */
