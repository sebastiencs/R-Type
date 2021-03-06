#ifndef TASKSCHEDULER_HH
#define TASKSCHEDULER_HH

#include "IThread.hh"
#include "Thread.hh"
#include "ITimer.hh"
#include "Timer.hh"

class TaskScheduler {
public:
	TaskScheduler(const Callback_t &_callback, const long _t);
	virtual ~TaskScheduler();

	void loop();
	void stop();
	void run();

private:
	IThread_SharedPtr thread;
	long interval;
	Callback_t callcack;
	ITimer_SharedPtr timer;
	bool running;
	Callback_t fptr;
};

using TaskScheduler_SharedPtr = std::shared_ptr<TaskScheduler>;

#endif
