#include <ScrollView.hh>

ScrollView::ScrollView(IGraphicEngine *engine)
{
	this->engine = engine;
}

ScrollView::~ScrollView()
{
	for (Cell *cell : listCell)
		engine->eraseTextField(cell->getId());
}

void ScrollView::createCell()
{
	static unsigned int i = 0;

	listCell.push_front(new Cell(std::to_string(i), Transformation(50, 50), "COUCOU", 4, engine));
	++i;
}

void ScrollView::isSelect()
{
}


Cell::Cell(const std::string& id, const Transformation& transformation, const std::string& name, const int nbrPlayers, IGraphicEngine *engine)
{
	this->engine = engine;

	this->id = id;
	this->name = name;
	this->nbrPlayers = nbrPlayers;
	engine->displayTextField(name, transformation, 32, "Fipps.otf", Color::White, "" + id);
}

const std::string& Cell::getId() const
{
	return id;
}
