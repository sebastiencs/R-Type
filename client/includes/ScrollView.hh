#ifndef SCROLL_VIEW_HH_
# define SCROLL_VIEW_HH_

#include <list>
#include "IGraphicEngine.hh"
#include "ICallBack.hh"
#include "Cell.hh"

class ScrollView : public IDrawable, public ICallback
{
public:
	ScrollView(IGraphicEngine *engine);
	virtual ~ScrollView();

	void createCell(const std::string& name, int nbr);
	void isSelect();

	//IDrawable
	virtual const std::string& getId() const;
	virtual void draw();

	//ICallback
	virtual void onAction();
	virtual void onHover(uint32_t x, uint32_t y);
	virtual bool isPressed(uint32_t x, uint32_t y) const;
	virtual const callback& getCallback() const;

private:
	IGraphicEngine *engine;
	std::list<Cell *> listCell;
	std::list<Cell *> displayedCell;
	std::string selectedCell;
	std::string id;
};

#endif /* !SCROLL_VIEW_HH_ */