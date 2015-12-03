#ifndef CELL_HH
# define CELL_HH

# include <iostream>
# include <string>
//# include "IGraphicEngine.hh"
//# include "TextField.hh"
# include "Drawable.hpp"
# include "ICallBack.hh"
# include "SFML/Graphics/Sprite.hpp"
#include "ScrollView.hh"

class IGraphicEngine;
class TextField;

class Cell : public Drawable, public ICallback
{
public:
	Cell(const std::string&  id, const Transformation& transformation,
		const std::string& name, const int nbrPlayers, IGraphicEngine *engine,
		ScrollView *_superView);
	virtual ~Cell();

	const std::string& getNameParty();
	int getNbrPlayers();

	//Drawable
	virtual void draw();
	virtual void setTransformation(const Transformation& t);


	//ICallback
	virtual bool onAction(uint32_t x, uint32_t y);
	virtual void onHover(uint32_t x, uint32_t y);
	virtual bool isPressed(uint32_t x, uint32_t y) const;
	virtual const callback& getCallback() const;

private:
	IGraphicEngine *engine;
	TextField *textField;

	std::string nameParty;
	int nbrPlayers;
	ScrollView *superView;
};

#endif
