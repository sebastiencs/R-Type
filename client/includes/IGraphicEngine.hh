#ifndef IGRAPHICENGINE_H_
# define IGRAPHICENGIN_H_

# include <iostream>

class IGraphicEngine {
	virtual void createWindow(uint16_t sizeX, uint16_t sizeY, const std::string& title) = 0;

	template <typename T>
	virtual T* loadImageFromFile(const std::string& path) = 0;

	template <typename T>
	virtual void drawImage(const T& source, uint16_t x, uint16_t y) = 0;

	virtual void repaint() = 0;
};

#endif /* !IGRAPHICENGINE */