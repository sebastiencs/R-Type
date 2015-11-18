#ifndef GRAPHIC_ENGINE_H_
# define GRAPHIC_ENGINE_H_

# include <thread>
#	include <iostream>
#	include <chrono>
# include <map>
# include <SFML\Window\Window.hpp>
# include <SFML\Graphics\RenderWindow.hpp>
# include <SFML\Window\Event.hpp>
# include <SFML\Graphics\Image.hpp>
# include <SFML\Graphics\Texture.hpp>
# include <SFML\Graphics\Sprite.hpp>
# include "IGraphicEngine.hh"

# define RS_PATH "ressources/"

class GraphicEngine : public IGraphicEngine {
public:

	~GraphicEngine();

	virtual void createWindow(uint16_t sizeX, uint16_t sizeY, const std::string& title);
	virtual bool loadImageFromFile(const std::string& file);
	virtual void drawImage(const std::string& name, uint16_t x, uint16_t y);
	virtual void handleEvents();
	virtual void repaint();
	virtual void launch();

protected:
	sf::RenderWindow* window;
	std::map<std::string, sf::Texture*> cachedImages;

};
#endif /*! GRAPHIC_ENGINE_H_ */