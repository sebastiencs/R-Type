#include <ScrollView.hh>
#include "Cell.hh"
#include "Button.hh"
#include "Box.hh"

ScrollView::ScrollView(const Transformation& transformation, int nbrDiplayCell, IGraphicEngine_SharedPtr eng)
  : engine(std::move(eng))
{
	callback fptr;

	this->nbrDiplayCell = nbrDiplayCell;
	this->_transformation = transformation;
	this->_id = "ScrollView";
	this->_visible = true;

	nbrCell = 0;
	base = 0;
	boxCells = std::make_shared<Box>(Orientation::vertical, _transformation, _id + "Box");

	fptr = std::bind(&ScrollView::decrBase, this);
	buttons.push_back(std::make_shared<Button>("Up", "ArrowUp.png", Transformation(transformation.getX() + transformation.getWidth(), transformation.getY()), Color::None, fptr, "Up", engine));

	fptr = std::bind(&ScrollView::incrBase, this);
	buttons.push_back(std::make_shared<Button>("Down", "ArrowDown.png", Transformation(transformation.getX() + transformation.getWidth(), transformation.getY() + transformation.getHeight()), Color::None, fptr, "Down", engine));
}

ScrollView::~ScrollView()
{
	boxCells->clearElements();
	buttons.clear();
}

void ScrollView::createCell(const std::string& name, int nbr)
{
  boxCells->addDrawable(std::make_shared<Cell>(std::to_string(nbrCell), Transformation(_transformation.getX(), _transformation.getY()), name, nbr, engine, this));
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
	if (base < (static_cast<int>(boxCells->getElements().size()) - nbrDiplayCell))
		++base;
}

void ScrollView::decrBase()
{
	if (base > 0)
		--base;
}

const std::list<Drawable_SharedPtr>& ScrollView::getListCell() const
{
	return boxCells->getElements();
}

const std::string & ScrollView::getSelectCell() const
{
	return selectedCell;
}

void ScrollView::setSelectedCell(const std::string & id)
{
	selectedCell = id;
}

void ScrollView::draw()
{
	int i = 0;

	boxCells->updateTransformation();
	for (auto &c : boxCells->getElements()) {
		if (i >= base && i < (base + nbrDiplayCell)) {
			c->setVisible(true);
			c->draw();
		}
		++i;
	}
	for (auto &b : buttons)
		b->draw();
}

bool ScrollView::onAction(uint32_t x, uint32_t y)
{
	int i = 0;

	boxCells->updateTransformation();
	for (auto &c : boxCells->getElements()) {
		if (i >= base && i < (base + nbrDiplayCell))
			if (ICallback *tmp = dynamic_cast<ICallback*>(c.get()))
				if (tmp->onAction(x, y)) {
					return true;
				}
		++i;
	}
	for (auto &b : buttons)
		if (b->onAction(x, y)) {
			return true;
		}
	return false;
}

void ScrollView::onHover(uint32_t x, uint32_t y)
{
	int i = 0;

	boxCells->updateTransformation();
	for (auto &c : boxCells->getElements()) {
		if (i >= base && i < (base + nbrDiplayCell)) {
			if (ICallback *tmp = dynamic_cast<ICallback*>(c.get()))
				tmp->onHover(x, y);
		}
		++i;
	}
	for (auto &b : buttons)
		b->onHover(x, y);
}

bool ScrollView::isPressed(uint32_t x, uint32_t y) const
{
	uint32_t mx = _transformation.getX();
	uint32_t my = _transformation.getY();
	uint32_t mwidth = _transformation.getWidth();
	uint32_t mheight = _transformation.getHeight();
	return (x >= mx && x <= (mx + mwidth) &&
		y >= my && y <= (my + mheight) && _visible);
}

const callback & ScrollView::getCallback() const
{
	return *(new callback());
}
