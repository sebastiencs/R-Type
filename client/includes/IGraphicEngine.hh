#ifndef IGRAPHICENGINE_H_
# define IGRAPHICENGINE_H_

# include <iostream>
#include <functional>
# include "Transformation.hh"
# include "Color.hh"

typedef std::function<void()> callback;
typedef std::function<void(uint32_t, uint32_t)> mouseCallback;

class IGraphicEngine {
public:
	virtual ~IGraphicEngine() {};

	virtual void createWindow(uint16_t sizeX, uint16_t sizeY, const std::string& title) = 0;
	
	virtual void displayButton(const std::string& txt, const std::string & img, const Transformation & t, const Color & color, callback fptr = nullptr, const std::string& id = 0) = 0;
	virtual void displayTextField(const std::string& _text, const Transformation& t, uint16_t size, const std::string& font, const Color& color, const std::string& _id) = 0;
	virtual void eraseButton(const std::string& txt) = 0;
	virtual void eraseTextField(const std::string & id) = 0;

	virtual void drawImage(const std::string& name, const Transformation& transformation, const Color& color = Color::None) = 0;
	virtual void drawSplitImage(const std::string& name, const Transformation& transformation, const Color& color) = 0;
	
	virtual void drawText(const std::string& text, const Transformation& transformation,
		uint16_t size, const Color& color = Color::White, const std::string& font = "") = 0;

	virtual void setCallbackFunction(callback, void* arg) = 0;

	virtual void handleEvents() = 0;
	virtual void launch() = 0;

	virtual int getWindowWidth() const = 0;
	virtual int getWindowHeight() const = 0;
};

#endif /* !IGRAPHICENGINE */
