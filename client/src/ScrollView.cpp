#include <ScrollView.hh>


ScrollView::ScrollView(const Transformation& transformation, int nbrDiplayCell, IGraphicEngine *engine)
{
	this->nbrDiplayCell = nbrDiplayCell;
	this->engine = engine;
	this->transformation = transformation;
	nbrCell = 0;
	base = 0;

	callback fptr;
	fptr = std::bind(&ScrollView::decrBase, this);
	buttons.push_back(new Button("Up", "ArrowUp.png", Transformation(transformation.getX() + transformation.getWidth(), transformation.getY()), Color::None, fptr, "Up", engine));

	fptr = std::bind(&ScrollView::incrBase, this);
	buttons.push_back(new Button("Down", "ArrowDown.png", Transformation(transformation.getX() + transformation.getWidth(), transformation.getY() + transformation.getHeight()), Color::None, fptr, "Down", engine));
}

ScrollView::~ScrollView()
{
	for (Cell *cell : listCell) {
		delete(cell);
	}
	for (Button *b : buttons)
		delete(b);
}

void ScrollView::createCell(const std::string& name, int nbr)
{
	listCell.push_back(new Cell(std::to_string(nbrCell), Transformation(transformation.getX(), transformation.getY()), name, nbr, engine));
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

void ScrollView::incrBase()
{
	if (base < ((int)listCell.size() - nbrDiplayCell))
		++base;
}

void ScrollView::decrBase()
{
	if (base > 0)
		--base;
}

const std::list<Cell*>& ScrollView::getListCell() const
{
	return listCell;
}

const std::string & ScrollView::getSelectCell() const
{
	return selectedCell;
}

const std::string & ScrollView::getId() const
{
	return id;
}

void ScrollView::draw()
{
	int i = 0;

	for (Cell *c : listCell) {
		if (i >= base && i < (base + nbrDiplayCell)) {
			c->getTransformation().setPosition(transformation.getX(), (transformation.getY() + 50) + (i - base) * 32);
			c->draw();
		}
		++i;
	}
	for (Button *b : buttons)
		b->draw();
}

const Transformation & ScrollView::getTransformation() const
{
	return *(new Transformation());
}

void ScrollView::onAction()
{
}

void ScrollView::onHover(uint32_t x, uint32_t y)
{
	int i = 0;
	for (Cell *c : listCell) {
		if (i >= base && i < (base + nbrDiplayCell))
			c->onHover(x, y);
		++i;
	}
	for (Button *b : buttons)
		b->onHover(x, y);
}

bool ScrollView::isPressed(uint32_t x, uint32_t y) const
{
	int i = 0;
	for (Cell *c : listCell) {
		if (i >= base && i < (base + nbrDiplayCell))
			if (c->isPressed(x, y)) {
				c->onAction();
				const_cast<ScrollView *>(this)->selectedCell = c->getId();
			}
		++i;
	}
	for (Button *b : buttons)
		if (b->isPressed(x, y))
			b->onAction();
	return false;
}

const callback & ScrollView::getCallback() const
{
	return *(new callback());
}

