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

Cell::Cell(const std::string& id, const Transformation& transformation, const std::string& name, const int nbrPlayers, IGraphicEngine *engine)
{
	_id = id;

	std::string txt = "[";
	txt += name;
	txt += "]";
	txt += "   ";
	txt += std::to_string(nbrPlayers);
	txt += "/4";
	engine->displayTextField(txt, transformation, 22, "Fipps.otf", Color::White, "TextField" + _id);
}

Cell::~Cell()
{
	std::string id;
	id = "TextField" + _id;
	engine->eraseTextField(id);
}

const std::string& Cell::getId() const
{
	return _id;
}
