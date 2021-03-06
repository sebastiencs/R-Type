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
	Box(const Orientation orientation, const Transformation& transformation, const std::string& id, const bool deleteChilds = true);
	virtual ~Box();

	void addDrawable(Drawable_SharedPtr drawable, const int32_t pos = -1);
	void removeDrawable(Drawable_SharedPtr drawable);
	void setSpacing(const uint16_t spacing);
	void setOrientation(const Orientation orientation);

	Drawable_SharedPtr getElement(const std::string& id);
	const std::list<Drawable_SharedPtr>& getElements() const;
	void clearElements();
	void setElementVisibility(const std::string& id, const bool);
	void setElementVisibility(Drawable_SharedPtr &, const bool);

	void updateTransformation();

	// IDrawable
	virtual void draw();
	virtual void setTransformation(const Transformation& t);

	// ICallback
	virtual bool onAction(const uint32_t x, const uint32_t y);
	virtual void onHover(const uint32_t x, const uint32_t y);
	virtual bool isPressed(const uint32_t x, const uint32_t y) const;
	virtual const callback& getCallback() const;

protected:
	bool isUpdated;
	Orientation orientation;
	uint16_t spacing;
  	bool shouldDeleteChilds;
	std::list<Drawable_SharedPtr> elementsList;
};

using Box_SharedPtr = std::shared_ptr<Box>;

#endif /* !BOX_HH_ */
