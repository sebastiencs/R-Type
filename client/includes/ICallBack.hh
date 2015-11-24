#ifndef ICALLBACK_H_
# define ICALLBACK_H_
	
class ICallBack
{
public:
	virtual ~ICallBack() {}
	virtual void onAction(void *arg) = 0;
};

#endif