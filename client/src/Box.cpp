#include <algorithm>
#include "Box.hh"
#include "Tools.hh"

Box::Box(const Orientation orientation, const Transformation& transformation, const std::string& id, const bool deleteChilds) :
	isUpdated(false),
	orientation(orientation),
	spacing(0),
	shouldDeleteChilds(deleteChilds)
{
	_transformation = transformation;
	_id = id;
	_visible = true;
}

Box::~Box()
{
	if (shouldDeleteChilds)
		clearElements();
}

void Box::addDrawable(Drawable_SharedPtr drawable, const int32_t pos)
{
	isUpdated = false;
	auto it = elementsList.begin();
	if (pos != -1) {
		for (int32_t tmp = 0; tmp < pos; ++tmp)
			++it;
		elementsList.insert(it, drawable);
	}
	else
		elementsList.push_back(drawable);
}

void Box::removeDrawable(Drawable_SharedPtr drawable)
{
	isUpdated = false;

	auto func = [&drawable] (auto &id) { return (id == drawable); };
	elementsList.remove_if(func);
}

void Box::setSpacing(const uint16_t spacing)
{
	isUpdated = false;
	this->spacing = spacing;
}

void Box::setOrientation(const Orientation orientation)
{
	isUpdated = false;
	this->orientation = orientation;
}

Drawable_SharedPtr Box::getElement(const std::string & id)
{
	return (Tools::findIn(elementsList, [&id] (auto &b) { return (b->getId() == id); }));
}

const std::list<Drawable_SharedPtr>& Box::getElements() const
{
	return elementsList;
}

void Box::clearElements()
{
	auto clearFunc = [](auto &) { return (true); };

	elementsList.remove_if(clearFunc);
	elementsList.clear();
	isUpdated = false;
}

void Box::setElementVisibility(const std::string & id, const bool v)
{
	auto &&d = Tools::findIn(elementsList, [&id](auto &b) { return (b->getId() == id); });
	if (d) {
		d->setVisible(v);
		isUpdated = false;
	}
}

void Box::setElementVisibility(Drawable_SharedPtr &toFind, const bool v)
{
	auto &&d = Tools::findIn(elementsList, [toFind](auto &b) { return (b == toFind); });
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
	for (auto &d : elementsList)
		d->draw();
}

void Box::setTransformation(const Transformation & t)
{
	_transformation = t;
	isUpdated = false;
	updateTransformation();
}

bool Box::onAction(const uint32_t x, const uint32_t y)
{
	if (isPressed(x, y)) {
		for (auto &d : elementsList)
			if (ICallback* dc = dynamic_cast<ICallback*>(d.get()))
				if (dc->onAction(x, y)) {
					return true;
				}
	}
	return false;
}

void Box::onHover(const uint32_t x, const uint32_t y)
{
	for (auto &d : elementsList)
		if (ICallback* dc = dynamic_cast<ICallback*>(d.get()))
			dc->onHover(x, y);
}

bool Box::isPressed(const uint32_t x, const uint32_t y) const
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
	for (auto &d : elementsList) {
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
