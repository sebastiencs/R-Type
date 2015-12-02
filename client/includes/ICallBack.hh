#ifndef ICALLBACK_H_
# define ICALLBACK_H_

# include <iostream>
# include <functional>

typedef std::function<void()> callback;
//class callback;

class ICallback
{
public:
	virtual ~ICallback() {}
	virtual void onAction() = 0;
	virtual void onHover(uint32_t x, uint32_t y) = 0;
	virtual bool isPressed(uint32_t x, uint32_t y) const = 0;
	virtual const callback& getCallback() const = 0;
};

#endif
