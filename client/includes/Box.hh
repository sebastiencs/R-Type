#ifndef BOX_HH_
# define BOX_HH_

# include <list>
# include "Drawable.hpp"
# include "ICallBack.hh"

class IDrawable;

enum Orientation {
	vertical = 0,
	horizontal
};

class Box : public Drawable, public ICallback {
public:
	Box(Orientation orientation, const Transformation& transformation, const std::string& id);

	void addDrawable(Drawable* drawable, int32_t pos = -1);
	void removeDrawable(Drawable* drawable);
	void setSpacing(uint16_t spacing);
	void setOrientation(Orientation orientation);

	Drawable* getElement(const std::string& id);
	const std::list<Drawable *> getElements() const;
	void clearElements();

	void updateTransformation();

	// IDrawable
	virtual void draw();

	// ICallback
	virtual bool onAction(uint32_t x, uint32_t y);
	virtual void onHover(uint32_t x, uint32_t y);
	virtual bool isPressed(uint32_t x, uint32_t y) const;
	virtual const callback& getCallback() const;

protected:
	bool isUpdated;
	Orientation orientation;
	uint16_t spacing;
	std::list<Drawable* > elementsList;
};

#endif /* !BOX_HH_ */