#ifndef GRAPHIC_ENGINE_H_
# define GRAPHIC_ENGINE_H_

# include <thread>
#	include <iostream>
#	include <chrono>
# include <SFML\Window\Window.hpp>
# include <SFML\Window\Event.hpp>
# include "IGraphicEngine.hh"

class GraphicEngine : public IGraphicEngine {
public:
	virtual void createWindow(uint16_t sizeX, uint16_t sizeY, const std::string& title);

	virtual bool loadImageFromFile(const std::string& path);

	void drawImage(const std::string& name, uint16_t x, uint16_t y);

	virtual void handleEvents();

	virtual void repaint();
};
#endif /*! GRAPHIC_ENGINE_H_ */