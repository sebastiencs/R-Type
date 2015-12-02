#include <ScrollView.hh>


ScrollView::ScrollView(const Transformation& transformation, int nbrDiplayCell, IGraphicEngine *engine)
{
	callback fptr;
	
	this->nbrDiplayCell = nbrDiplayCell;
	this->engine = engine;
	this->_transformation = transformation;
	this->_id = "ScrollView";

	nbrCell = 0;
	base = 0;
	boxCells = new Box(Orientation::vertical, _transformation, _id);

	fptr = std::bind(&ScrollView::decrBase, this);
	buttons.push_back(new Button("Up", "ArrowUp.png", Transformation(transformation.getX() + transformation.getWidth(), transformation.getY()), Color::None, fptr, "Up", engine));

	fptr = std::bind(&ScrollView::incrBase, this);
	buttons.push_back(new Button("Down", "ArrowDown.png", Transformation(transformation.getX() + transformation.getWidth(), transformation.getY() + transformation.getHeight()), Color::None, fptr, "Down", engine));
}

ScrollView::~ScrollView()
{
	boxCells->clearElements();
	delete boxCells;
	for (Button *b : buttons)
		delete(b);
}

void ScrollView::createCell(const std::string& name, int nbr)
{
		boxCells->addDrawable(new Cell(std::to_string(nbrCell), Transformation(_transformation.getX(), _transformation.getY()), name, nbr, engine));
//	boxCells->addDrawable(new TextField(name, Transformation(_transformation.getX(), _transformation.getY()), 22, "Fipps.otf", Color::Red, std::to_string(nbrCell), engine));
	++nbrCell;
}

void ScrollView::emptyCell()
{
	boxCells->clearElements();
	nbrCell = 0;
	base = 0;
}

void ScrollView::incrBase()
{
	if (base < ((int)boxCells->getElements().size() - nbrDiplayCell))
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

void ScrollView::draw()
{
	int i = 0;

	if (nbrCell > 0)
		boxCells->draw();
	for (Button *b : buttons)
		b->draw();
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

