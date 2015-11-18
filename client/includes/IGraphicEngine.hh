#ifndef IGRAPHICENGINE_H_
# define IGRAPHICENGINE_H_

# include <iostream>

class IGraphicEngine {
public:
	virtual void createWindow(uint16_t sizeX, uint16_t sizeY, const std::string& title) = 0;

	virtual bool loadImageFromFile(const std::string& path) = 0;

	virtual void drawImage(const std::string& name, uint16_t x, uint16_t y) = 0;

	// a compléter ?
	virtual void handleEvents() = 0;

	virtual void launch() = 0;

	virtual void repaint() = 0;
};

#endif /* !IGRAPHICENGINE */
