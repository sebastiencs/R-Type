#ifndef GRAPHIC_ENGINE_H_
# define GRAPHIC_ENGINE_H_

# include <thread>
#	include <iostream>
#	include <chrono>
# include <map>
# include <SFML/Window/Window.hpp>
# include <SFML/Graphics/RenderWindow.hpp>
# include <SFML/Window/Event.hpp>
# include <SFML/Graphics/Image.hpp>
# include <SFML/Graphics/Font.hpp>
# include <SFML/Graphics/Text.hpp>
# include <SFML/Graphics/Texture.hpp>
# include <SFML/Graphics/Sprite.hpp>
# include "IGraphicEngine.hh"

# define RS_PATH "ressources/"
# define FONT_PATH "ressources/fonts/"
# define DEFAULT_FONT "default.ttf"
# define DEFAULT_FONT_SIZE 12

class GraphicEngine : public IGraphicEngine {

public:
	~GraphicEngine();

	virtual void createWindow(uint16_t sizeX, uint16_t sizeY, const std::string& title);
	virtual void drawImage(const std::string& name, const Transformation& transformation, const Color& color = Color::None);
	virtual void drawText(const std::string& text, const Transformation& transformation,
		uint16_t size, const Color& color = Color::White, const std::string& font = "");
	virtual void handleEvents();
	virtual void repaint();
	virtual void launch();

protected:
	bool loadImageFromFile(const std::string& file);
	bool loadFontFromFile(const std::string& file);


	sf::RenderWindow* window;
	std::map<std::string, sf::Texture*> cachedImages;
	std::map<std::string, sf::Font*> cachedFonts;

};
#endif /*! GRAPHIC_ENGINE_H_ */