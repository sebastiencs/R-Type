#ifndef ICALLBACK_H_
# define ICALLBACK_H_

# include <iostream>
# include <functional>

typedef std::function<void()> callback;

class ICallback
{
public:
	virtual ~ICallback() {}
	virtual bool onAction(const uint32_t x, const uint32_t y) = 0;
	virtual void onHover(const uint32_t x, const uint32_t y) = 0;
	virtual bool isPressed(const uint32_t x, const uint32_t y) const = 0;
	virtual const callback& getCallback() const = 0;
};

#endif
