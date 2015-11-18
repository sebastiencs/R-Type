#include "GraphicEngine.hh"


void GraphicEngine::createWindow(uint16_t sizeX, uint16_t sizeY, const std::string & title)
{
	sf::Window window(sf::VideoMode(sizeX, sizeY), title);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
}

void GraphicEngine::handleEvents()
{
}

void GraphicEngine::repaint()
{
}

bool GraphicEngine::loadImageFromFile(const std::string& path)
{
	return false;
}

void GraphicEngine::drawImage(const std::string& name, uint16_t x, uint16_t y)
{
}

