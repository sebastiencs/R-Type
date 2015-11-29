#ifndef SCROLL_VIEW_HH_
# define SCROLL_VIEW_HH_

# include "GraphicEngine.hh"
# include "ICallBack.hh"

class Cell
{
public:
	Cell(const std::string&  id, const Transformation& transformation, const std::string& name, const int nbrPlayers, IGraphicEngine *engine);
	virtual ~Cell();

	const std::string& getId() const;
private:
	IGraphicEngine *engine;
	std::string _id;
};

class ScrollView
{
public:
	ScrollView(IGraphicEngine *engine);
	virtual ~ScrollView();

	void createCell(const std::string& name, int nbr);
	void isSelect();

private:
	IGraphicEngine *engine;
	std::list<Cell *> listCell;
};

#endif /* !SCROLL_VIEW_HH_ */