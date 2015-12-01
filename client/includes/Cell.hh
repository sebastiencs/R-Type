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

	//Drawable
	virtual const sf::Sprite& getSprite() const;
	virtual void draw();

	//ICallback
	virtual void onAction();
	virtual void onHover(uint32_t x, uint32_t y);
	virtual bool isPressed(uint32_t x, uint32_t y) const;
	virtual const callback& getCallback() const;

private:
	IGraphicEngine *engine;
	std::string _id;
	int nbrPlayers;
	std::string nameParty;

	//draw
	TextField *textField;
};

#endif
