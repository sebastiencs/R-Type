#ifndef SCROLL_VIEW_HH_
# define SCROLL_VIEW_HH_

# include "GraphicEngine.hh"
# include "ICallBack.hh"

class Cell
{
public:
	Cell(const std::string&  id, const Transformation& transformation, const std::string& name, const int nbrPlayers, IGraphicEngine *engine);
	~Cell() {}

	const std::string& getId() const;
private:
	IGraphicEngine *engine;
	std::string name;
	std::string id;
	int nbrPlayers;
	bool isSelect;
};

class ScrollView
{
public:
	ScrollView(IGraphicEngine *engine);
	~ScrollView();

	void createCell();
	void isSelect();

private:
	IGraphicEngine *engine;
	std::list<Cell *> listCell;
};

#endif /* !SCROLL_VIEW_HH_ */