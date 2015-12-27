#ifndef CREDITS_HH
# define CREDITS_HH

# include <iostream>
# include <string>
# include "Transformation.hh"
# include "IGraphicEngine.hh"
# include "TextField.hh"
# include "ScrollView.hh"
# include "Debug.hh"

class Credits
{
public:
	Credits(IGraphicEngine_SharedPtr engine);
	virtual ~Credits();

	virtual void draw();

private:
	IGraphicEngine_SharedPtr engine;
	std::list<TextField_SharedPtr> authors;
};

#endif /* !CREDITS_HH */
