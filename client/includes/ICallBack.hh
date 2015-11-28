#ifndef ICALLBACK_H_
# define ICALLBACK_H_
	
class ICallback
{
public:
	virtual ~ICallback() {}
	virtual void onAction(/*void *arg*/) = 0;
	virtual void onHover(uint32_t x, uint32_t y) = 0;
	virtual bool isPressed(uint32_t x, uint32_t y) const = 0;
	virtual const void* getArgs() const = 0;
	virtual const std::function<void()>& getCallback() const = 0;
};

#endif