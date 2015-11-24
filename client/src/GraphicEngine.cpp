#include "GraphicEngine.hh"

GraphicEngine::GraphicEngine(Packager* packager) : _packager(packager)
{
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

IGraphicEngine::~IGraphicEngine() {};

void GraphicEngine::createWindow(uint16_t sizeX, uint16_t sizeY, const std::string & title)
{
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
		// TODO: get les paquets ?
		if (_timer.ms() >= MS_REFRESH)
		{
			window->clear(sf::Color::Black);
			// TODO: faire l'interface en fct des paquets
			while (PackageStorage::getInstance().getObstaclesPackage() != nullptr) {
				const PaquetObstacle* p = PackageStorage::getInstance().getObstaclesPackage();
				drawImage(obstacleTypeToSpriteString[p->getType()], Transformation(p->getX(), p->getY()));
				PackageStorage::getInstance().deleteObstaclesPackage();
			}
			while (PackageStorage::getInstance().getPlayersPackage() != nullptr) {
				const PaquetPlayerCoord* p = PackageStorage::getInstance().getPlayersPackage();
				drawImage(playerIDToSpriteString[p->getPlayerID()], Transformation(p->getX(), p->getY()));
				PackageStorage::getInstance().deletePlayersPackage();
			}
			while (PackageStorage::getInstance().getShotsPackage() != nullptr) {
				const PaquetPlayerShot* p = PackageStorage::getInstance().getShotsPackage();
				drawImage(shotTypeToSpriteString[p->getType()], Transformation(p->getX(), p->getY()));
				PackageStorage::getInstance().deleteShotsPackage();
			}

			drawImage("r-typesheet26.gif", Transformation(0, 0));
			/* test */
			static unsigned int i = 0;
			static unsigned int j = 0;
			if (i > 6) {
				i = 0;
				j++;
			}
			if (j > 1)
				j = 0;
			drawSplitImage("r-typesheet23.gif", Transformation(100, 100), Color::None, i * 34, j * 33, 34, 33);
			i++;
			drawText("DefaultText", Transformation(50, 50), DEFAULT_FONT_SIZE);
			drawText("OtherText", Transformation(80, 80), 20, Color::White, "Fipps.otf");
			/* END TEST */

			window->display();
			_timer.reset();
		}
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

void GraphicEngine::drawSplitImage(const std::string & name, const Transformation & t, const Color & color, const int x, const int y, const int width, const int height)
{
	if (cachedImages.find(name) == cachedImages.end() &&
		!loadImageFromFile(name)) {
		std::cerr << "Couldn't open texture file: \"" << name << "\"" << std::endl;
		return;
	}
	sf::IntRect subRect;
	subRect.left = x;
	subRect.top = y;
	subRect.width = width;
	subRect.height = height;
	sf::Sprite sprite(*cachedImages[name], subRect);
	if (t.hasPosition())
		sprite.setPosition(t.getX(), t.getY());
	if (t.hasRotation())
		sprite.rotate(t.getRotation());
	if (color.isUsed())
		sprite.setColor(sf::Color(color.getColor()));
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

