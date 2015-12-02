#include "Box.hh"

Box::Box(Orientation orientation, const Transformation& transformation, const std::string& id)
	: orientation(orientation), isUpdated(false)
{
	_transformation = transformation;
	_id = id;
	spacing = 0;
}

void Box::addDrawable(Drawable* drawable, uint32_t pos)
{
	isUpdated = false;
	std::list<Drawable* >::iterator it = elementsList.begin();
	if (pos != -1) {
		for (uint32_t tmp = 0; tmp < pos; ++tmp)
			++it;
		elementsList.insert(it, drawable);
	}
	else
		elementsList.push_back(drawable);
}

void Box::removeDrawable(Drawable * drawable)
{
	isUpdated = false;
	for (Drawable* id : elementsList)
		if (id == drawable) {
			elementsList.remove(drawable);
			break;
		}
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
	for (Drawable *b : elementsList)
		if (b->getId() == id)
			return (b);
	return (nullptr);
}

void Box::clearElements()
{
	for (Drawable *b : elementsList) {
		elementsList.pop_front();
		delete b;
	}
	elementsList.clear();
}

void Box::draw()
{
	if (!isUpdated)
		updateTransformation();
	for (IDrawable* d : elementsList)
		d->draw();
}

void Box::onAction()
{
}

void Box::onHover(uint32_t x, uint32_t y)
{
	for (Drawable* d : elementsList)
		if (ICallback* dc = dynamic_cast<ICallback*>(d))
			dc->onHover(x, y);
}

bool Box::isPressed(uint32_t x, uint32_t y) const
{
	for (Drawable* d : elementsList)
		if (ICallback* dc = dynamic_cast<ICallback*>(d))
			if (dc->isPressed(x, y)) {
				dc->onAction();
				return true;
			}
	return false;
}

const callback & Box::getCallback() const
{
	return nullptr;
}

void Box::updateTransformation()
{
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
