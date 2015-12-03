#ifndef IDRAWABLE_H_
# define IDRAWABLE_H_

//# include "IGraphicEngine.hh"

#include "Transformation.hh"

class IDrawable
{
public:
	virtual ~IDrawable() {}

	virtual const Transformation& getTransformation() const = 0;
	virtual const std::string& getId() const = 0;
	virtual bool isVisible() const = 0;

	virtual void setId(std::string&) = 0;
	virtual void setTransformation(const Transformation&) = 0;
	virtual void setVisible(bool) = 0;

	virtual void draw() = 0;
};

#endif /* !IDRAWABLE_H_ */
