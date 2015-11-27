#ifndef IGRAPHICENGINE_H_
# define IGRAPHICENGINE_H_

# include <iostream>
# include "Transformation.hh"
# include "Color.hh"

typedef void(*callback)(void*);

class IGraphicEngine {
public:
	virtual ~IGraphicEngine() {};

	virtual void createWindow(uint16_t sizeX, uint16_t sizeY, const std::string& title) = 0;
	virtual void displayButton(const std::string& txt, const std::string & img, const Transformation & t, const Color & color, callback fptr = nullptr, void* arg = nullptr) = 0;

	virtual void drawImage(const std::string& name, const Transformation& transformation, const Color& color = Color::None) = 0;
	virtual void drawSplitImage(const std::string& name, const Transformation& transformation, const Color& color) = 0;
	virtual void drawText(const std::string& text, const Transformation& transformation,
		uint16_t size, const Color& color = Color::White, const std::string& font = "") = 0;

	virtual void setCallbackFunction(callback, void* arg) = 0;

	virtual void handleEvents() = 0;
	virtual void launch() = 0;
	virtual void repaint() = 0;
};

#endif /* !IGRAPHICENGINE */
