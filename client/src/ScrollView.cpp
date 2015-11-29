#include <ScrollView.hh>

ScrollView::ScrollView(IGraphicEngine *engine)
{
	nbrCell = 0;
	this->engine = engine;
}

ScrollView::~ScrollView()
{
	for (Cell *cell : listCell) {
		delete(cell);
	}
}

void ScrollView::createCell(const std::string& name, int nbr)
{
	listCell.push_back(new Cell(std::to_string(nbrCell), Transformation(350, 230 + nbrCell * 32), name, nbr, engine));
	displayedCell.push_back(new Cell(std::to_string(nbrCell), Transformation(350, 230 + nbrCell * 32), name, nbr, engine));
	++nbrCell;
}

void ScrollView::emptyCell()
{
	for (Cell *c : displayedCell)
		delete(c);
	for (Cell *c : listCell)
		delete(c);
	listCell.clear();
	displayedCell.clear();
	nbrCell = 0;
}

void ScrollView::isSelect()
{
}

const std::string & ScrollView::getId() const
{
	return id;
}

void ScrollView::draw()
{
	for (Cell *c : displayedCell) {
		c->draw();
	}
}

void ScrollView::onAction()
{

}

void ScrollView::onHover(uint32_t x, uint32_t y)
{
	for (Cell *c : displayedCell) {
		c->onHover(x, y);
	}
}

bool ScrollView::isPressed(uint32_t x, uint32_t y) const
{
	for (Cell *c : displayedCell) {
		if (c->isPressed(x, y) == true)
			return true;
	}
	return false;
}

const callback & ScrollView::getCallback() const
{
	return nullptr;
}

