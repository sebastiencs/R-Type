#ifndef CREDITS_HH
# define CREDITS_HH
  
# include <iostream>
# include <string>
# include "Transformation.hh"
# include "IGraphicEngine.hh"
# include "TextField.hh"
# include "ScrollView.hh"

class Credits
{
public:
	Credits(IGraphicEngine *engine);
	virtual ~Credits();

	virtual void draw();

private:
	IGraphicEngine *engine;
	std::list<TextField *> authors;
};

#endif /* !CREDITS_HH */
