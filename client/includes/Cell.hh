#ifndef CELL_HH
#define CELL_HH

#include <iostream>
#include <string>
#include "Transformation.hh"
#include "IGraphicEngine.hh"
#include "ICallBack.hh"
#include "IDrawable.hh"
#include "TextField.hh"

class Cell : public IDrawable, public ICallback
{
public:
	Cell(const std::string&  id, const Transformation& transformation, const std::string& name, const int nbrPlayers, IGraphicEngine *engine);
	virtual ~Cell();

	//IDrawable
	virtual const sf::Sprite& getSprite() const;
	const std::string& getId() const;
	virtual void draw();
	const Transformation& getTransformation() const;
	virtual Transformation & getTransformation();

	//ICallback
	virtual void onAction();
	virtual void onHover(uint32_t x, uint32_t y);
	virtual bool isPressed(uint32_t x, uint32_t y) const;
	virtual const callback& getCallback() const;

private:
	IGraphicEngine *engine;
	std::string _id;

	//draw
	TextField *textField;
};

#endif