#include <ScrollView.hh>

ScrollView::ScrollView()
{
}

void ScrollView::isSelect()
{
}


Cell::Cell(int id, const Transformation& transformation, const std::string& name, const int nbrPlayers, IGraphicEngine *engine)
{
	std::function<void()> fptr;

	this->engine = engine;

	this->id = id;
	this->name = name;
	this->nbrPlayers = nbrPlayers;

//	fptr = std::bind(&ScrollView::isSelect, this);
//	engine->displayButton(name, "cell.png", transformation, Color::None, fptr, id);
}
