#include "Cell.hh"
#include "TextField.hh"
#include "Debug.hh"

Cell::Cell(const std::string& id, const Transformation& transformation, const std::string& name, const int nbrPlayers, IGraphicEngine *engine, ScrollView *_superView)
{
	_id = id;
	_transformation = transformation;
	_visible = true;

	nameParty = name;

	this->nbrPlayers = nbrPlayers;
	superView = _superView;

	std::string txt = '[' + name + ']' + "\t\t" + std::to_string(nbrPlayers) + "/4";

	textField = new TextField(txt, _transformation, 22, "Fipps.otf", Color::White, "TextField" + _id, engine);
	_transformation.setBounds(textField->getTransformation().getWidth(), textField->getTransformation().getHeight());
}

Cell::~Cell()
{
	delete textField;
}

const std::string & Cell::getNameParty()
{
	return nameParty;
}

int Cell::getNbrPlayers()
{
	return nbrPlayers;
}

void Cell::setTransformation(const Transformation& t) {
	_transformation = t;
	textField->setTransformation(t);
}

void Cell::draw()
{
	if (_visible)
		textField->draw();
}

bool Cell::onAction(uint32_t x, uint32_t y)
{
	if (isPressed(x, y)) {
		superView->setSelectedCell(_id);
		DEBUG_MSG(textField->getId() + " is selected");
		return true;
	}
	return false;
}

void Cell::onHover(uint32_t x, uint32_t y)
{
	if (isPressed(x, y)) {
		textField->setColor(Color::Darker);
	}
	else
		textField->setColor(Color::White);
}

bool Cell::isPressed(uint32_t x, uint32_t y) const
{
	uint32_t mx = _transformation.getX();
	uint32_t my = _transformation.getY();
	uint32_t mwidth = _transformation.getWidth();
	uint32_t mheight = _transformation.getHeight();
	return (x >= mx && x <= (mx + mwidth) &&
		y >= my && y <= (my + mheight) && _visible);
}

const callback& Cell::getCallback() const
{
	return *(new callback);
}
