#ifndef IGRAPHICENGINE_H_
# define IGRAPHICENGINE_H_


# include <iostream>
# include <functional>
# include "Transformation.hh"
# include "Color.hh"
# include "Text.hh"
# include "Sprite.hh"

# define RS_PATH "ressources/"
# define FONT_PATH "ressources/fonts/"
# define DEFAULT_FONT "default.ttf"
# define DEFAULT_FONT_SIZE 12
# define MS_REFRESH 33

typedef std::function<void()> callback;
typedef std::function<void(uint32_t, uint32_t)> mouseCallback;
typedef std::function<void(const char)> textEnteredCallback;

class IGraphicEngine {
public:
	virtual ~IGraphicEngine() {};

	virtual void createWindow(uint16_t sizeX, uint16_t sizeY, const std::string& title) = 0;

	virtual void drawImage(const std::string& name, const Transformation& transformation, const Color& color = Color::None) = 0;
	virtual void drawSplitImage(const std::string& name, const Transformation& transformation, const Color& color) = 0;

	virtual void drawSprite(const Sprite& sprite) = 0;
	virtual void drawText(const Text& text) = 0;
	virtual void drawText(const std::string& text, const Transformation& transformation,
		uint16_t size, const Color& color = Color::White, const std::string& font = "") = 0;

	virtual void setCallbackFunction(callback, void* arg) = 0;
	virtual void setMouseClickCallback(mouseCallback) = 0;
	virtual void setMouseMovedCallback(mouseCallback) = 0;
	virtual void setTextEnteredCallback(textEnteredCallback) = 0;

	virtual void handleEvents() = 0;
	virtual void launch() = 0;

	virtual int getWindowWidth() const = 0;
	virtual int getWindowHeight() const = 0;

	virtual void closeWindow() = 0;
};

#endif /* !IGRAPHICENGINE */
