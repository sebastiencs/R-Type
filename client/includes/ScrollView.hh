#ifndef SCROLL_VIEW_HH_
# define SCROLL_VIEW_HH_

#include <list>
#include "IGraphicEngine.hh"
#include "ICallBack.hh"
#include "Cell.hh"

class ScrollView : public IDrawable, public ICallback
{
public:
	ScrollView(int nbrDiplayCell, IGraphicEngine *engine);
	virtual ~ScrollView();

	void createCell(const std::string& name, int nbr);
	void emptyCell();
	void isSelect();

	void incrBase();
	void decrBase();


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
	Button *up;
	Button *down;
	std::string selectedCell;
	std::string id;

	int nbrCell;
	int nbrDiplayCell;
	int base;
};

#endif /* !SCROLL_VIEW_HH_ */