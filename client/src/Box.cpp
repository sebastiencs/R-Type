#include "Box.hh"
#include "Tools.hh"

Box::Box(Orientation orientation, const Transformation& transformation, const std::string& id)
	: orientation(orientation), isUpdated(false)
{
	_transformation = transformation;
	_id = id;
	spacing = 0;
}

void Box::addDrawable(Drawable* drawable, int32_t pos)
{
	isUpdated = false;
	std::list<Drawable* >::iterator it = elementsList.begin();
	if (pos != -1) {
		for (int32_t tmp = 0; tmp < pos; ++tmp)
			++it;
		elementsList.insert(it, drawable);
	}
	else
		elementsList.push_back(drawable);
	updateTransformation();
}

void Box::removeDrawable(Drawable * drawable)
{
	isUpdated = false;

	auto func = [&drawable] (Drawable *id) { return (id == drawable); };
	elementsList.remove_if(func);
	updateTransformation();
}

void Box::setSpacing(uint16_t spacing)
{
	isUpdated = false;
	this->spacing = spacing;
	updateTransformation();
}

void Box::setOrientation(Orientation orientation)
{
	isUpdated = false;
	this->orientation = orientation;
	updateTransformation();
}

Drawable* Box::getElement(const std::string & id)
{
	return (Tools::findIn(elementsList, [&id] (Drawable *b) { return (b->getId() == id); }));
}

const std::list<Drawable*> Box::getElements() const
{
	return elementsList;
}

void Box::clearElements()
{
	auto clearFunc = [] (Drawable *elem) { delete elem; return (true); };

	elementsList.remove_if(clearFunc);
	isUpdated = false;
	updateTransformation();
}

void Box::draw()
{
	if (!isUpdated)
		updateTransformation();
	for (IDrawable* d : elementsList)
		d->draw();
}

void Box::setTransformation(const Transformation & t)
{
	_transformation = t;
	isUpdated = false;
	updateTransformation();
}

bool Box::onAction(uint32_t x, uint32_t y)
{
	if (isPressed(x, y)) {
		for (Drawable* d : elementsList)
			if (ICallback* dc = dynamic_cast<ICallback*>(d))
				if (dc->onAction(x, y)) {
					return true;
				}
	}
	return false;
}

void Box::onHover(uint32_t x, uint32_t y)
{
	for (Drawable* d : elementsList)
		if (ICallback* dc = dynamic_cast<ICallback*>(d))
			dc->onHover(x, y);
}

bool Box::isPressed(uint32_t x, uint32_t y) const
{
	uint32_t mx = _transformation.getX();
	uint32_t my = _transformation.getY();
	uint32_t mwidth = _transformation.getWidth();
	uint32_t mheight = _transformation.getHeight();
	return (x >= mx && x <= (mx + mwidth) &&
		y >= my && y <= (my + mheight));
}

const callback & Box::getCallback() const
{
	return nullptr;
}

void Box::updateTransformation()
{
	if (_id == "leftBox")
		_id = _id;
	if (isUpdated || elementsList.empty())
		return;
	Transformation lastItemT = _transformation;
	bool first = true;
	for (Drawable* d : elementsList) {
		if (first) {
			Transformation newT(d->getTransformation());
			newT.setPosition(_transformation.getX(), _transformation.getY());
			d->setTransformation(newT);
			first = false;
		}
		else {
			uint16_t offsetX = (orientation == Orientation::horizontal ? lastItemT.getWidth() + spacing : 0);
			uint16_t offsetY = (orientation == Orientation::vertical ? lastItemT.getHeight() + spacing : 0);
			Transformation newT(d->getTransformation());
			newT.setPosition(lastItemT.getX() + offsetX, lastItemT.getY() + offsetY);
			d->setTransformation(newT);
		}
		lastItemT = d->getTransformation();
	}
	uint16_t boundX = (elementsList.back()->getTransformation().getX() + elementsList.back()->getTransformation().getWidth()) - _transformation.getX();
	uint16_t boundY = (elementsList.back()->getTransformation().getY() + elementsList.back()->getTransformation().getHeight()) - _transformation.getY();
	_transformation.setBounds(boundX, boundY);
	isUpdated = true;
}
