#ifndef SCROLL_VIEW_HH_
# define SCROLL_VIEW_HH_

# include <list>
# include "IGraphicEngine.hh"
# include "Drawable.hpp"
# include "ICallBack.hh"
//# include "Cell.hh"
//# include "Box.hh"

class Cell;
class Box;
class Button;

using Button_SharedPtr = std::shared_ptr<Button>;
using Box_SharedPtr = std::shared_ptr<Box>;

class ScrollView : public Drawable, public ICallback, public std::enable_shared_from_this<ScrollView>
{
public:
	ScrollView(const Transformation& transformation, const int nbrDiplayCell, IGraphicEngine_SharedPtr engine);
	virtual ~ScrollView();

	void createCell(const std::string& name, const int nbr);

	void emptyCell();

	void incrBase();
	void decrBase();

	const std::list<Drawable_SharedPtr>& getListCell() const;
	const std::string& getSelectCell() const;

	void setSelectedCell(const std::string& id);

	//Drawable
	virtual void draw();

	//ICallback
	virtual bool onAction(const uint32_t x, const uint32_t y);
	virtual void onHover(const uint32_t x, const uint32_t y);
	virtual bool isPressed(const uint32_t x, const uint32_t y) const;
	virtual const callback& getCallback() const;

private:
	IGraphicEngine_SharedPtr engine;
	Box_SharedPtr boxCells;

	std::list<Button_SharedPtr> buttons;

	std::string selectedCell;

	int nbrCell;
	int nbrDiplayCell;
	int base;
};

using ScrollView_SharedPtr = std::shared_ptr<ScrollView>;

#endif /* !SCROLL_VIEW_HH_ */
