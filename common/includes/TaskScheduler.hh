#ifndef TASKSCHEDULER_HH
#define TASKSCHEDULER_HH

#include "IThread.hh"
#include "Thread.hh"
#include "ITimer.hh"
#include "Timer.hh"

class TaskScheduler {
public:
	TaskScheduler(Callback_t _callback, long _t);
	~TaskScheduler();

	void loop();
private:
	IThread *thread;
	long interval;
	Callback_t callcack;
	ITimer *timer;
};

#endif