#include "Cell.hh"

Cell::Cell(const std::string& id, const Transformation& transformation, const std::string& name, const int nbrPlayers, IGraphicEngine *engine)
{
	_id = id;

	std::string txt = "[";
	txt += name;
	txt += "]";
	txt += "   ";
	txt += std::to_string(nbrPlayers);
	txt += "/4";

	textField = new TextField(txt, transformation, 22, "Fipps.otf", Color::White, "TextField" + _id, engine);
}

Cell::~Cell()
{
	/*std::string id;
	id = "TextField" + _id;
	engine->eraseTextField(id);*/
	delete textField;
}

const sf::Sprite & Cell::getSprite() const
{
	sf::Sprite *sprite = new sf::Sprite();
	return *sprite;
}

const std::string& Cell::getId() const
{
	return _id;
}

void Cell::draw()
{
	textField->draw();
}

void Cell::onAction()
{
}

void Cell::onHover(uint32_t x, uint32_t y)
{
	//if (isPressed(x, y)) {
	//	textField->getSprite().setColor(sf::Color(Color::Darker.getColor()));
	//}
	//else
	//	textField->getSprite().setColor(sf::Color::White);
}

bool Cell::isPressed(uint32_t x, uint32_t y) const
{
	return false;
}

const callback& Cell::getCallback() const
{
	return nullptr;
}
