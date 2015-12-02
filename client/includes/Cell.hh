#ifndef CELL_HH
# define CELL_HH

# include <iostream>
# include <string>
# include "IGraphicEngine.hh"
# include "TextField.hh"

class Cell : public Drawable, public ICallback
{
public:
	Cell(const std::string&  id, const Transformation& transformation, const std::string& name, const int nbrPlayers, IGraphicEngine *engine);
	virtual ~Cell();

	const std::string& getNameParty();
	int getNbrPlayers();
	const sf::Sprite& getSprite() const;

	//Drawable
	virtual void draw();
	virtual void setTransformation(const Transformation& t);


	//ICallback
	virtual void onAction();
	virtual void onHover(uint32_t x, uint32_t y);
	virtual bool isPressed(uint32_t x, uint32_t y) const;
	virtual const callback& getCallback() const;

private:
	IGraphicEngine *engine;
	TextField *textField;

	std::string nameParty;
	int nbrPlayers;
};

#endif
