#ifndef DRAWABLE_HPP_
# define DRAWABLE_HPP_

# include "IDrawable.hh"

class Drawable : public IDrawable
{
public:
	Drawable(){}
	virtual ~Drawable() {}
	virtual const Transformation& getTransformation() const {
		return (_transformation);
	}
	virtual void setTransformation(const Transformation& t) {
		_transformation = t;
	}
	virtual bool isVisible() const {
		return _visible;
	}

	virtual const std::string& getId() const {
		return _id;
	}
	virtual void setId(const std::string& id) {
		_id = id;
	}
	virtual void setVisible(const bool visible) {
		_visible = visible;
	}

protected:
	Transformation _transformation;
	std::string _id;
	bool _visible;
};

# include <memory>

using Drawable_SharedPtr = std::shared_ptr<Drawable>;

#endif /* !DRAWABLE_HPP_ */
