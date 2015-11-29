#ifndef SCROLL_VIEW_HH_
# define SCROLL_VIEW_HH_

#include <list>
#include "IGraphicEngine.hh"
#include "ICallBack.hh"
#include "Cell.hh"

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