#include "GraphicEngine.hh"
#include "Timer.hh"
#include "ListPlayers.hh"
#include "Sprite.hh"
#include "Text.hh"
#include "SystemAudio.hh"

sf::Time GraphicEngine::elapsedTime;

GraphicEngine::GraphicEngine()
{
	callbackArg = nullptr;
	call = nullptr;
	window = nullptr;
	_textEnteredcallback = nullptr;
	_usableKeyPressedCallback = nullptr;
	_timer = std::make_unique<Timer>();
	_timer->start();
	setInputMode(ZQSD);

	shotTypeToSpriteString[0] = "r-typesheet1.gif";
	shotTypeToSpriteString[1] = "r-typesheet1.gif";
	shotTypeToSpriteString[2] = "r-typesheet1.gif";
	shotTypeToSpriteString[3] = "r-typesheet1.gif";
	shotTypeToSpriteString[4] = "r-typesheet1.gif";
}

GraphicEngine::~GraphicEngine()
{
  std::cerr << "GRAPHIC ENGINE DELETED" << std::endl;
	cachedImages.clear();
}

void GraphicEngine::createWindow(uint16_t sizeX, uint16_t sizeY, const std::string & title)
{
	windowHeight = sizeY;
	windowWidth = sizeX;
	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(sizeX, sizeY), title, sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60);
}

void GraphicEngine::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		else if (event.type == sf::Event::TextEntered) {
			if (event.text.unicode < 128 && _textEnteredcallback)
				_textEnteredcallback(static_cast<char>(event.text.unicode));
		}
		if (_mouseClickCall && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			_mouseClickCall(event.mouseButton.x, event.mouseButton.y);
		else if (_mouseMoveCall && event.type == sf::Event::MouseMoved)
			_mouseMoveCall(event.mouseMove.x, event.mouseMove.y);
	}
}

void GraphicEngine::handleMovements()
{
	if (_usableKeyPressedCallback) {
		std::deque<UsableKeys> keys;

		if (sf::Keyboard::isKeyPressed(keyMap[UP]))
			keys.push_back(UsableKeys::Z);
		if (sf::Keyboard::isKeyPressed(keyMap[LEFT]))
			keys.push_back(UsableKeys::Q);
		if (sf::Keyboard::isKeyPressed(keyMap[DOWN]))
			keys.push_back(UsableKeys::S);
		if (sf::Keyboard::isKeyPressed(keyMap[RIGHT]))
			keys.push_back(UsableKeys::D);
		if (sf::Keyboard::isKeyPressed(keyMap[SPACEE]))
			keys.push_back(UsableKeys::SPACE);

		_usableKeyPressedCallback(keys);
	}
}

void GraphicEngine::setInputMode(InputMode mode)
{
	switch (mode) {
		case ZQSD:
			keyMap[KeyAlias::UP] = sf::Keyboard::Z;
			keyMap[KeyAlias::RIGHT] = sf::Keyboard::D;
			keyMap[KeyAlias::DOWN] = sf::Keyboard::S;
			keyMap[KeyAlias::LEFT] = sf::Keyboard::Q;
			keyMap[KeyAlias::SPACEE] = sf::Keyboard::Space;
			break;
		case ARROWS:
			keyMap[KeyAlias::UP] = sf::Keyboard::Up;
			keyMap[KeyAlias::RIGHT] = sf::Keyboard::Right;
			keyMap[KeyAlias::DOWN] = sf::Keyboard::Down;
			keyMap[KeyAlias::LEFT] = sf::Keyboard::Left;
			keyMap[KeyAlias::SPACEE] = sf::Keyboard::Space;
			break;
		case WASD:
			keyMap[KeyAlias::UP] = sf::Keyboard::W;
			keyMap[KeyAlias::RIGHT] = sf::Keyboard::D;
			keyMap[KeyAlias::DOWN] = sf::Keyboard::S;
			keyMap[KeyAlias::LEFT] = sf::Keyboard::A;
			keyMap[KeyAlias::SPACEE] = sf::Keyboard::Space;
		case PAD:
			break;
		default:
			break;
	}
}

void GraphicEngine::launch()
{
	if (!window)
		throw std::runtime_error("No window created, use createWindow function before using launch");
	sf::Clock clock;

	while (window->isOpen())
	{
		if (_timer->msWait(MS_REFRESH))
		{
			handleEvents();
			if (window->hasFocus()) {
			  handleMovements();
			}

			window->clear(sf::Color::Black);
			if (call)
				call();
			window->display();

			GraphicEngine::elapsedTime = clock.restart();
			_timer->reset();

		}
	}
}

void GraphicEngine::setCallbackFunction(callback fct, void * arg)
{
	call = fct;
	callbackArg = arg;
}

void GraphicEngine::setMouseClickCallback(mouseCallback call)
{
	_mouseClickCall = call;
}

void GraphicEngine::setMouseMovedCallback(mouseCallback call)
{
	_mouseMoveCall = call;
}

void GraphicEngine::setTextEnteredCallback(textEnteredCallback call)
{
	_textEnteredcallback = call;
}

const textEnteredCallback& GraphicEngine::getTextEnteredCallback()
{
	return _textEnteredcallback;
}

void GraphicEngine::setUsableKeyPressedCallback(usableKeyPressedCallback cb)
{
	_usableKeyPressedCallback = cb;
}

int GraphicEngine::getWindowWidth() const
{
	return windowWidth;
}

int GraphicEngine::getWindowHeight() const
{
	return windowHeight;
}

const sf::Texture& GraphicEngine::loadTexture(const std::string& img)
{
	if (cachedImages.find(img) == cachedImages.end() &&
		!loadImageFromFile(img)) {
		DEBUG_MSG("Couldn't open texture file: \"" << img << "\"");
		return *None;
	}
	return *cachedImages[img];
}

const sf::Font& GraphicEngine::loadFont(const std::string & font)
{
	if (cachedFonts.find(font) == cachedFonts.end() && !loadFontFromFile(font)) {
		DEBUG_MSG("Couldn't open font file: \"" << font << "\"");
		return *NoneFont;
	}
	return *cachedFonts[font];
}

void GraphicEngine::transformSprite(sf::Sprite& sprite, const Transformation& t, const Color& color)
{
	if (t.hasPosition())
		sprite.setPosition((float)t.getX(), (float)t.getY());
	if (t.hasRotation())
		sprite.rotate(t.getRotation());
	if (color.isUsed())
		sprite.setColor(sf::Color(color.getColor()));
	if (t.hasScale())
		sprite.setScale(t.getScaleX(), t.getScaleY());
}

void GraphicEngine::transformSprite(sf::Text& sprite, const Transformation& t, const Color& color)
{
	if (t.hasPosition())
		sprite.setPosition((float)t.getX(), (float)t.getY());
	if (t.hasRotation())
		sprite.rotate(t.getRotation());
	if (color.isUsed())
		sprite.setColor(sf::Color(color.getColor()));
	if (t.hasScale())
		sprite.setScale(t.getScaleX(), t.getScaleY());
}

bool GraphicEngine::loadImageFromFile(const std::string& file)
{
	if (cachedImages.find(file) != cachedImages.end())
		return true;

	Texture_SharedPtr texture = std::make_shared<sf::Texture>();
	if (!texture->loadFromFile(RS_PATH + file)) {
		return false;
	}
	cachedImages[file] = texture;
	return true;
}

bool GraphicEngine::loadFontFromFile(const std::string & file)
{
	if (cachedFonts.find(file) != cachedFonts.end())
		return true;

	Font_SharedPtr font = std::make_shared<sf::Font>();
	if (!font->loadFromFile(FONT_PATH + file)) {
		return false;
	}
	cachedFonts[file] = font;
	return true;
}

void GraphicEngine::drawImage(const std::string& name, const Transformation& t, const Color& color)
{
	if (cachedImages.find(name) == cachedImages.end() &&
		!loadImageFromFile(name)) {
		DEBUG_MSG("Couldn't open texture file: \"" << name << "\"");
		return;
	}
	sf::Sprite sprite(*cachedImages[name]);
	transformSprite(sprite, t, color);
	window->draw(sprite);
}

void GraphicEngine::drawSplitImage(const std::string & name, const Transformation & t, const Color & color)
{
	if (cachedImages.find(name) == cachedImages.end() &&
		!loadImageFromFile(name)) {
		DEBUG_MSG("Couldn't open texture file: \"" << name << "\"");
		return;
	}

	sf::IntRect subRect;
	if (t.hasCrop())
	{
		subRect.left = t.getCrop().at(Transformation::CROP::SRCX);
		subRect.top = t.getCrop().at(Transformation::CROP::SRCY);
		subRect.width = t.getCrop().at(Transformation::CROP::SRCWIDTH);
		subRect.height = t.getCrop().at(Transformation::CROP::SRCHEIGHT);
	}
	else
	{
		subRect.left = 0;
		subRect.top = 0;
		subRect.width = cachedImages[name]->getSize().x;
		subRect.height = cachedImages[name]->getSize().x;
	}

	sf::Sprite sprite(*cachedImages[name], subRect);
	transformSprite(sprite, t, color);
	window->draw(sprite);
}

void GraphicEngine::drawSplitImage(Sprite& sprite)
{
	//	transformSprite(sprite, t, color);
	if (!sprite.hasEngine())
		sprite.setEngine(this);
	sprite.draw();
}

void GraphicEngine::drawSprite(Sprite& sprite)
{
	if (!sprite.hasEngine())
		sprite.setEngine(this);

	sprite.draw();
}

void GraphicEngine::drawSprite(const sf::Sprite & sprite)
{
	window->draw(sprite);
}

void GraphicEngine::drawText(Text& text)
{
	if (!text.hasEngine())
		text.setEngine(this);
	text.draw();
}
void GraphicEngine::drawText(const sf::Text & text)
{
	window->draw(text);
}

void GraphicEngine::drawText(const std::string& text, const Transformation& t,
	uint16_t size, const Color& color, const std::string& font)
{
	std::string fontName = (font == "" ? DEFAULT_FONT : font);
	if (cachedFonts.find(fontName) == cachedFonts.end() &&
		!loadFontFromFile(fontName)) {
		DEBUG_MSG("Couldn't open font file: \"" << font << "\"");
		return;
	}
	sf::Text textToDraw;
	textToDraw.setFont(*cachedFonts[fontName]);
	textToDraw.setString(text);
	textToDraw.setCharacterSize(size);
	transformSprite(textToDraw, t, color);
	window->draw(textToDraw);
}

void GraphicEngine::closeWindow()
{
	if (window->isOpen()) {
		window->close();
	}
}

int32_t GraphicEngine::getDeltaTimeMS()
{
	DEBUG_MSG("getDeltaTime: " << GraphicEngine::elapsedTime.asMilliseconds() / 20);
	return GraphicEngine::elapsedTime.asMilliseconds() / 20;
}

float GraphicEngine::getDeltaTimeS()
{
	return GraphicEngine::elapsedTime.asSeconds();
}

const sf::Texture* GraphicEngine::None = new sf::Texture();
const sf::Font* GraphicEngine::NoneFont = new sf::Font();
