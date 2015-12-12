#include "GraphicEngine.hh"
#include "Timer.hh"
#include "ListPlayers.hh"
#include "Packager.hh"
#include "Sprite.hh"
#include "Text.hh"
#include "SystemAudio.hh"

GraphicEngine::GraphicEngine(Packager* packager) : _packager(packager)
{
	callbackArg = nullptr;
	call = nullptr;
	window = nullptr;
	_textEnteredcallback = nullptr;
	_timer = new Timer();
	_timer->start();
	_shotCooldown = new Timer();
	_shotCooldown->start();

	playerIDToSpriteString[0] = "r-typesheet42.gif";
	playerIDToSpriteString[1] = "r-typesheet42.gif";
	playerIDToSpriteString[2] = "r-typesheet42.gif";
	playerIDToSpriteString[3] = "r-typesheet42.gif";
	playerIDToSpriteString[4] = "r-typesheet42.gif";

	shotTypeToSpriteString[0] = "r-typesheet1.gif";
	shotTypeToSpriteString[1] = "r-typesheet1.gif";
	shotTypeToSpriteString[2] = "r-typesheet1.gif";
	shotTypeToSpriteString[3] = "r-typesheet1.gif";
	shotTypeToSpriteString[4] = "r-typesheet1.gif";
}

GraphicEngine::~GraphicEngine()
{
	if (window)
		delete window;
	for (std::map<std::string, sf::Texture *>::iterator it = cachedImages.begin(); it != cachedImages.end(); ++it)
		if (it->second)
			delete it->second;
	cachedImages.clear();
	if (_timer)
		delete _timer;
	if (_shotCooldown)
		delete _shotCooldown;
}

void GraphicEngine::createWindow(uint16_t sizeX, uint16_t sizeY, const std::string & title)
{
	windowHeight = sizeY;
	windowWidth = sizeX;
	window = new sf::RenderWindow(sf::VideoMode(sizeX, sizeY), title, sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60);
}

void GraphicEngine::handleEvents()
{
	sf::Event event;
	// ListPlayers &LP = ListPlayers::getInstance();
	// Player *player = LP.getPlayer(LP.getId());
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		else if (event.type == sf::Event::TextEntered) {
			if (event.text.unicode < 128 && _textEnteredcallback)
				_textEnteredcallback(static_cast<char>(event.text.unicode));
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			_mouseClickCall(event.mouseButton.x, event.mouseButton.y);
		else if (event.type == sf::Event::MouseMoved)
			_mouseMoveCall(event.mouseMove.x, event.mouseMove.y);
	}
}

void GraphicEngine::handleMovements()
{
	ISystemAudio &audio = SystemAudio::getInstance();
	ListPlayers &LP = ListPlayers::getInstance();
	Player *player = LP.getPlayer(LP.getId());
	bool changed = false;
	bool bullet = false;
	if (!player)
		return;

	Position pos = player->getPosition();

	uint16_t playerVelocity = (uint16_t)(300 * getDeltaTimeS());
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && pos.y >= 10) {
			// Si S est appuyer en meme temps le mec bouge pas.
			pos.y -= playerVelocity;
			changed = true;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && pos.x >= 10) {
			pos.x -= playerVelocity;
			changed = true;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && pos.y <= 715) {
			pos.y += playerVelocity;
			changed = true;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && pos.x <= 910) {
			pos.x += playerVelocity;
			changed = true;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _shotCooldown->ms() > SHOT_COOLDOWN) {
		audio.playSound(ISystemAudio::SIMPLE_SHOT);
		_shotCooldown->reset();
		bullet = true;
	}
	if (changed) {
		player->setPosition(pos);
		_packager->createMovementPackage(LP.getId(), pos.x, pos.y);
	}
	if (bullet) {
		player->setPosition(pos);
		_packager->createShotPackage(LP.getId(), 1, pos.x, pos.y);
		player->addBullet(Position(pos.x, pos.y));
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

			elapsedTime = clock.restart();
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

	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(RS_PATH + file)) {
		delete texture;
		return false;
	}
	cachedImages[file] = texture;
	return true;
}

bool GraphicEngine::loadFontFromFile(const std::string & file)
{
	if (cachedFonts.find(file) != cachedFonts.end())
		return true;

	sf::Font* font = new sf::Font();
	if (!font->loadFromFile(FONT_PATH + file)) {
		delete font;
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

int32_t GraphicEngine::getDeltaTimeMS() const
{
	DEBUG_MSG("getDeltaTime: " << elapsedTime.asMilliseconds() / 20);
	return elapsedTime.asMilliseconds() / 20;
}

float GraphicEngine::getDeltaTimeS() const
{
	return elapsedTime.asSeconds();
}

const sf::Texture* GraphicEngine::None = new sf::Texture();
const sf::Font* GraphicEngine::NoneFont = new sf::Font();
