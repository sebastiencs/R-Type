#ifndef IDRAWABLE_H_
# define IDRAWABLE_H_

//# include "GraphicEngine.hh"
# include <SFML/Graphics/Sprite.hpp>
# include "Transformation.hh"

class IDrawable
{
public:
	virtual ~IDrawable() {}
	/*virtual const sf::Sprite& getSprite() const = 0;*/
	/*virtual const std::string& getTextureName() const = 0;*/
	/*virtual const Color& getColor() const = 0;
	virtual const std::string& getName() const = 0;*/
	/*virtual const bool getVisible() const = 0;
	virtual void setVisible(bool visible) = 0;*/
	virtual const Transformation& getTransformation() const = 0;
	virtual const std::string& getId() const = 0;
	virtual void draw() = 0;
};

#endif /* !IDRAWABLE_H_ */
