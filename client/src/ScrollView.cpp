#include <ScrollView.hh>

ScrollView::ScrollView(IGraphicEngine *engine)
{
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
	static unsigned int i = 0;

	listCell.push_back(new Cell(std::to_string(i), Transformation(350, 230), name, nbr, engine));
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

