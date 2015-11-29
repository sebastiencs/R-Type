#include <ScrollView.hh>

ScrollView::ScrollView(int nbrDiplayCell, IGraphicEngine *engine)
{
	this->nbrDiplayCell = nbrDiplayCell;
	this->engine = engine;
	std::function<void()> fptr;
	fptr = std::bind(&ScrollView::incrBase, this);
	up = new Button("Up", "ArrowUp.png", Transformation(650, 200), Color::None, fptr, "Up", engine);

	fptr = std::bind(&ScrollView::decrBase, this);
	down = new Button("Down", "ArrowDown.png", Transformation(650, 200 + 32 * 9), Color::None, fptr, "Down", engine);
	nbrCell = 0;
	base = 0;
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
	++nbrCell;
}

void ScrollView::emptyCell()
{
	for (Cell *c : listCell)
		delete(c);
	listCell.clear();
	nbrCell = 0;
	base = 0;
}

void ScrollView::isSelect()
{
}

void ScrollView::incrBase()
{
	DEBUG_MSG("Increment Base");
	if (base < (listCell.size() - nbrDiplayCell))
		++base;
}

void ScrollView::decrBase()
{
	DEBUG_MSG("Decrement Base");
	if (base > 0)
		--base;
}

const std::string & ScrollView::getId() const
{
	return id;
}

void ScrollView::draw()
{
	int i = base;

	for (Cell *c : listCell) {
		if (i < (base + nbrDiplayCell))
			c->draw();
		++i;
	}
	up->draw();
	down->draw();
}

void ScrollView::onAction()
{

}

void ScrollView::onHover(uint32_t x, uint32_t y)
{
	int i = 0;

	for (Cell *c : listCell) {
		if (i < (base + nbrDiplayCell))
			c->onHover(x, y);
		++i;
	}
	up->onHover(x, y);
	down->onHover(x, y);
}

bool ScrollView::isPressed(uint32_t x, uint32_t y) const
{
	for (Cell *c : listCell) {
		if (c->isPressed(x, y) == true)
			;
	}
	if (up->isPressed(x, y))
		up->onAction();
	if (down->isPressed(x, y))
		down->onAction();
	return false;
}

const callback & ScrollView::getCallback() const
{
	return nullptr;
}

