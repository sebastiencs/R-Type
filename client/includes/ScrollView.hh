#ifndef SCROLL_VIEW_HH_
# define SCROLL_VIEW_HH_

# include "GraphicEngine.hh"
# include "ICallBack.hh"

class Cell
{
public:
	Cell(int id, const Transformation& transformation, const std::string& name, const int nbrPlayers, IGraphicEngine *engine);
	~Cell() {}

private:

	IGraphicEngine *engine;
	std::string name;
	int id;
	int nbrPlayers;
	bool isSelect;
};

class ScrollView
{
public:
	ScrollView();
	~ScrollView() {}

	void isSelect();

private:
	std::list<Cell *> listCell;
};

#endif /* !SCROLL_VIEW_HH_ */