#include <ScrollView.hh>

ScrollView::ScrollView()
{
}

void ScrollView::isSelect()
{
}


Cell::Cell(int id, const Transformation& transformation, const std::string& name, const int nbrPlayers, IGraphicEngine *engine)
{
	this->engine = engine;

	this->id = id;
	this->name = name;
	this->nbrPlayers = nbrPlayers;

	engine->displayTextField(name, transformation, 32, "Fipps.otf", Color::White, "" + id);
}
