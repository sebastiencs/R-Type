#ifndef CELL_HH
# define CELL_HH

# include <iostream>
# include <string>
# include "TextField.hh"
# include "Drawable.hpp"
# include "ICallBack.hh"
# include "SFML/Graphics/Sprite.hpp"
# include "ScrollView.hh"

class IGraphicEngine;
class TextField;

using TextField_SharedPtr = std::shared_ptr<TextField>;

class Cell : public Drawable, public ICallback
{
public:
	Cell(const std::string&  id, const Transformation& transformation,
		const std::string& name, const int nbrPlayers, IGraphicEngine_SharedPtr &engine,
		ScrollView_SharedPtr _superView);
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
	TextField_SharedPtr textField;

	std::string nameParty;
	int nbrPlayers;
	ScrollView_SharedPtr superView;
};

#endif
