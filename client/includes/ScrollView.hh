#ifndef SCROLL_VIEW_HH_
# define SCROLL_VIEW_HH_

#include <list>
#include "IGraphicEngine.hh"
#include "ICallBack.hh"
#include "Cell.hh"

class ScrollView : public IDrawable, public ICallback
{
public:
	ScrollView(Transformation transformation, int nbrDiplayCell, IGraphicEngine *engine);
	virtual ~ScrollView();

	void createCell(const std::string& name, int nbr);

	void emptyCell();

	void incrBase();
	void decrBase();

	void joinButton();

	//IDrawable
	virtual const std::string& getId() const;
	virtual void draw();
	virtual const Transformation & getTransformation() const;

	//ICallback
	virtual void onAction();
	virtual void onHover(uint32_t x, uint32_t y);
	virtual bool isPressed(uint32_t x, uint32_t y) const;
	virtual const callback& getCallback() const;

private:
	IGraphicEngine *engine;
	Transformation transformation;
	std::list<Cell *> listCell;
	std::list<Button* > buttons;
	std::string selectedCell;
	std::string id;

	int nbrCell;
	int nbrDiplayCell;
	int base;
};

#endif /* !SCROLL_VIEW_HH_ */