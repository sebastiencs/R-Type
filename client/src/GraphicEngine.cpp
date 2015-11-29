#include "GraphicEngine.hh"

GraphicEngine::GraphicEngine(Packager* packager) : _packager(packager)
{
	callbackArg = nullptr;
	call = nullptr;
	_timer.start();
	obstacleTypeToSpriteString[0] = "r-typesheet17.gif";
	obstacleTypeToSpriteString[1] = "r-typesheet17.gif";
	obstacleTypeToSpriteString[2] = "r-typesheet17.gif";
	obstacleTypeToSpriteString[3] = "r-typesheet17.gif";
	obstacleTypeToSpriteString[4] = "r-typesheet17.gif";
	obstacleTypeToSpriteString[5] = "r-typesheet17.gif";

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
}

void GraphicEngine::createWindow(uint16_t sizeX, uint16_t sizeY, const std::string & title)
{
	windowHeight = sizeY;
	windowWidth = sizeX;
	window = new sf::RenderWindow(sf::VideoMode(sizeX, sizeY), title);
	window->setFramerateLimit(60);
}

void GraphicEngine::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		// TODO: Trouver quoi faire des positions du joueur
		if (event.type == sf::Event::Closed)
			window->close();
		else if (event.key.code == sf::Keyboard::Space)
			_packager->createShotPackage(0, 0, 0, 0);
		else if (event.key.code == sf::Keyboard::Z)
			_packager->createMovementPackage(0, 0, 0);
		else if (event.key.code == sf::Keyboard::Q)
			_packager->createMovementPackage(0, 0, 0);
		else if (event.key.code == sf::Keyboard::S)
			_packager->createMovementPackage(0, 0, 20);
		else if (event.key.code == sf::Keyboard::D)
			_packager->createMovementPackage(0, 20, 0);
		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			for (std::list<ICallback *>::iterator it = elements.begin(); it != elements.end(); it++)
				if ((*it)->isPressed(event.mouseButton.x, event.mouseButton.y) == true)
					(*it)->onAction();
		}
		else if (event.type == sf::Event::MouseMoved)
			for (std::list<ICallback *>::iterator it = elements.begin(); it != elements.end(); it++) {
				(*it)->onHover(event.mouseMove.x, event.mouseMove.y);
			}
	}
}

void GraphicEngine::repaint()
{
}

void GraphicEngine::launch()
{
	while (window->isOpen())
	{
		if (_timer.ms() >= MS_REFRESH)
		{
			handleEvents();
			window->clear(sf::Color::Black);

			// a mettre dans la callback?
			for (std::list<ICallback *>::iterator it = elements.begin(); it != elements.end(); it++) {
				if (IDrawable* drawable = dynamic_cast<IDrawable*>((*it)))
					window->draw(drawable->getSprite());
			}

			// temporaire : seulement pour les textfield en attendant de fix l'interface
			for (IDrawable* element : dElements) {
					TextField *tf = static_cast<TextField *>(element);
					tf->displayText();
			}
			if (call)
				call();
			window->display();
			_timer.reset();
		}
	}
}

void GraphicEngine::setCallbackFunction(callback fct, void * arg)
{
	call = fct;
	callbackArg = arg;
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
		std::cerr << "Couldn't open texture file: \"" << img << "\"" << std::endl;
		return *None;
	}
	return *cachedImages[img];
}

void GraphicEngine::transformSprite(sf::Sprite& sprite, const Transformation& t, const Color& color)
{
	if (t.hasPosition())
		sprite.setPosition(t.getX(), t.getY());
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
	if (!texture->loadFromFile(RS_PATH + file))
		return false;
	cachedImages[file] = texture;
	return true;
}

bool GraphicEngine::loadFontFromFile(const std::string & file)
{
	if (cachedFonts.find(file) != cachedFonts.end())
		return true;

	sf::Font* font = new sf::Font();
	if (!font->loadFromFile(FONT_PATH + file))
		return false;
	cachedFonts[file] = font;
	return true;
}

void GraphicEngine::displayButton(const std::string& txt, const std::string & img, const Transformation & t, const Color & color, callback fptr, const std::string& id)
{
	for (ICallback* element : elements) {
		if (IDrawable* b = dynamic_cast<IDrawable* >(element))
			if (b->getId() == id)
				return;
	}
	if (cachedImages.find(img) == cachedImages.end() &&
		!loadImageFromFile(img)) {
		std::cerr << "Couldn't open texture file: \"" << img << "\"" << std::endl;
		return;
	}
	elements.push_front(new Button(txt, img, t, color, fptr, id, this));
}

void GraphicEngine::eraseButton(const std::string & id)
{
	for (std::list<ICallback *>::iterator it = elements.begin(); it != elements.end(); it++) {
		if (IDrawable* b = dynamic_cast<IDrawable*>((*it)))
			if (b->getId() == id) {
				elements.remove(*it);
				return;
			}

	}
}

void GraphicEngine::eraseTextField(const std::string & id)
{
	for (IDrawable* element : dElements) {
		if (element->getId() == id) {
			dElements.remove(element);
			delete(element);
			return;
		}
	}

}

void GraphicEngine::drawImage(const std::string& name, const Transformation& t, const Color& color)
{
	if (cachedImages.find(name) == cachedImages.end() &&
		!loadImageFromFile(name)) {
		std::cerr << "Couldn't open texture file: \"" << name << "\"" << std::endl;
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
		std::cerr << "Couldn't open texture file: \"" << name << "\"" << std::endl;
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

void GraphicEngine::displayTextField(const std::string & _text, const Transformation & t, uint16_t size, const std::string & font, const Color & color, const std::string & _id)
{
	for (IDrawable* element : dElements) {
		if (element->getId() == _id) {
			return;
		}
	}
	TextField * tf = new TextField(_text, t, size, font, color, _id, this);
	dElements.push_front(tf);
}

void GraphicEngine::drawText(const std::string& text, const Transformation& t,
	uint16_t size, const Color& color, const std::string& font)
{
	std::string fontName = (font == "" ? DEFAULT_FONT : font);
	if (cachedFonts.find(fontName) == cachedFonts.end() &&
		!loadFontFromFile(fontName)) {
		std::cerr << "Couldn't open font file: \"" << fontName << "\"" << std::endl;
		return;
	}
	sf::Text textToDraw;
	textToDraw.setFont(*cachedFonts[fontName]);
	textToDraw.setString(text);
	textToDraw.setCharacterSize(size);
	if (t.hasPosition())
		textToDraw.setPosition(t.getX(), t.getY());
	if (color.isUsed())
		textToDraw.setColor(sf::Color(color.getColor()));
	window->draw(textToDraw);
}

const sf::Texture* GraphicEngine::None = new sf::Texture();