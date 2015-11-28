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

void ScrollView::createCell()
{
	static unsigned int i = 0;

	listCell.push_front(new Cell(std::to_string(i), Transformation(350, 230), "La party des Bg", 2, engine));
	++i;
	listCell.push_front(new Cell(std::to_string(i), Transformation(350, 260), "Nique Ta mère", 1, engine));
	++i;
	listCell.push_front(new Cell(std::to_string(i), Transformation(350, 290), "Boris == Bego", 4, engine));
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
