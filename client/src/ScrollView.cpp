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
