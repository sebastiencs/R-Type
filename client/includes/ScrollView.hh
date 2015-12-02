#ifndef SCROLL_VIEW_HH_
# define SCROLL_VIEW_HH_

# include <list>
# include "IGraphicEngine.hh"
# include "Cell.hh"
# include "Box.hh"

class ScrollView : public Drawable, public ICallback
{
public:
	ScrollView(const Transformation& transformation, int nbrDiplayCell, IGraphicEngine *engine);
	virtual ~ScrollView();

	void createCell(const std::string& name, int nbr);

	void emptyCell();

	void incrBase();
	void decrBase();

	const std::list<Cell *>& getListCell() const;
	const std::string& getSelectCell() const;

	//Drawable
	virtual void draw();

	//ICallback
	virtual void onAction();
	virtual void onHover(uint32_t x, uint32_t y);
	virtual bool isPressed(uint32_t x, uint32_t y) const;
	virtual const callback& getCallback() const;

private:
	IGraphicEngine *engine;
	Box *boxCells;

	std::list<Cell *> listCell;
	std::list<Button* > buttons;

	std::string selectedCell;

	int nbrCell;
	int nbrDiplayCell;
	int base;
};

#endif /* !SCROLL_VIEW_HH_ */