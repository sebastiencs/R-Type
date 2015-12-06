#include <algorithm>
#include "Box.hh"
#include "Tools.hh"

Box::Box(Orientation orientation, const Transformation& transformation, const std::string& id)
	: isUpdated(false), orientation(orientation), spacing(0)
{
	_transformation = transformation;
	_id = id;
	_visible = true;
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
}

void Box::removeDrawable(Drawable * drawable)
{
	isUpdated = false;

	auto func = [&drawable] (Drawable *id) { return (id == drawable); };
	elementsList.remove_if(func);
}

void Box::setSpacing(uint16_t spacing)
{
	isUpdated = false;
	this->spacing = spacing;
}

void Box::setOrientation(Orientation orientation)
{
	isUpdated = false;
	this->orientation = orientation;
}

Drawable* Box::getElement(const std::string & id)
{
	return (Tools::findIn(elementsList, [&id] (Drawable *b) { return (b->getId() == id); }));
}

const std::list<Drawable*>& Box::getElements() const
{
	return elementsList;
}

void Box::clearElements()
{
	auto clearFunc = [] (Drawable *elem) { delete elem; return (true); };

	elementsList.remove_if(clearFunc);
	isUpdated = false;
}

void Box::setElementVisibility(const std::string & id, bool v)
{
	Drawable* d = Tools::findIn(elementsList, [&id](Drawable *b) { return (b->getId() == id); });
	if (d) {
		d->setVisible(v);
		isUpdated = false;
	}
}

void Box::setElementVisibility(Drawable * toFind, bool v)
{
	Drawable* d = Tools::findIn(elementsList, [toFind](Drawable *b) { return (b == toFind); });
	if (d) {
		d->setVisible(v);
		isUpdated = false;
	}
}

void Box::draw()
{
	if (!_visible)
		return;
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
		y >= my && y <= (my + mheight) && _visible);
}

const callback & Box::getCallback() const
{
	return *(new callback);
}

#define MAX(a, b) ((a < b) ? (b) : (a))

void Box::updateTransformation()
{
	if (isUpdated || elementsList.empty())
		return;
	Transformation lastItemT = _transformation;
	uint16_t boundWidth = 0;
	uint16_t boundHeight = 0;
	bool first = true;
	for (Drawable* d : elementsList) {
		if (d->isVisible()) {
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
			boundWidth = (orientation == Orientation::horizontal ? boundWidth + d->getTransformation().getWidth() + spacing : MAX(boundWidth, d->getTransformation().getWidth()));
			boundHeight = (orientation == Orientation::horizontal ? MAX(boundHeight, d->getTransformation().getHeight()) : boundHeight + d->getTransformation().getHeight() + spacing);
			lastItemT = d->getTransformation();
		}
	}
	if (orientation == Orientation::horizontal) {
		_transformation.setBounds(boundWidth - spacing, boundHeight);
	} else {
		_transformation.setBounds(boundWidth, boundHeight - spacing);
	}
	isUpdated = true;
}
