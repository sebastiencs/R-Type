#include <ScrollView.hh>

ScrollView::ScrollView(int nbrDiplayCell, IGraphicEngine *engine)
{
	this->nbrDiplayCell = nbrDiplayCell;
	this->engine = engine;
	up = new Button("Up", "ArrowUp.png", Transformation(650, 200), Color::None, nullptr, "Up", engine);
	down = new Button("Down", "ArrowDown.png", Transformation(650, 200 + 32 * 9), Color::None, nullptr, "Down", engine);
	nbrCell = 0;
}

ScrollView::~ScrollView()
{
	for (Cell *cell : listCell) {
		delete(cell);
	}
	delete(up);
	delete(down);
}

void ScrollView::createCell(const std::string& name, int nbr)
{
	listCell.push_back(new Cell(std::to_string(nbrCell), Transformation(350, 230 + nbrCell * 32), name, nbr, engine));
	if (nbrCell < nbrDiplayCell)
		displayedCell.push_back(new Cell(std::to_string(nbrCell), Transformation(350, 230 + displayedCell.size() * 32), name, nbr, engine));
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
	up->draw();
	down->draw();
}

void ScrollView::onAction()
{

}

void ScrollView::onHover(uint32_t x, uint32_t y)
{
	for (Cell *c : displayedCell) {
		c->onHover(x, y);
	}
	up->onHover(x, y);
	down->onHover(x, y);
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

