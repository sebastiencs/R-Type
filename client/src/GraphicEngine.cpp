#include "GraphicEngine.hh"

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
	window = new sf::RenderWindow(sf::VideoMode(sizeX, sizeY), title);
	window->setFramerateLimit(30);
}

void GraphicEngine::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

void GraphicEngine::repaint()
{
}

void GraphicEngine::launch()
{
	while (window->isOpen())
	{
		handleEvents();
		window->clear(sf::Color::Black);

		drawImage("r-typesheet26.gif", Transformation(0, 0));
		drawText("DefaultText", Transformation(50, 50), DEFAULT_FONT_SIZE);
		drawText("OtherText", Transformation(80, 80), 20, Color::White, "Fipps.otf");
		// TODO: Timer, paquets etc

		window->display();
	}
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



void GraphicEngine::drawImage(const std::string& name, const Transformation& t, const Color& color)
{
	if (cachedImages.find(name) == cachedImages.end() &&
		!loadImageFromFile(name)) {
		std::cerr << "Couldn't open texture file: \"" << name << "\"" << std::endl;
		return;
	}
	sf::Sprite sprite(*cachedImages[name]);
	if (t.hasPosition())
		sprite.setPosition(t.getX(), t.getY());
	if (t.hasRotation())
		sprite.rotate(t.getRotation());
	if (color.isUsed())
		sprite.setColor(sf::Color(color.getColor()));
	// TODO: crop if asked
	window->draw(sprite);
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

