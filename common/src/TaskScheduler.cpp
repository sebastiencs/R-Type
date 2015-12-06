#include "TaskScheduler.hh"

TaskScheduler::TaskScheduler(Callback_t _callback, long _t)
{
	callcack = _callback;
	interval = _t;
	Callback_t fptr = [this](void *) {this->loop(); return nullptr; };
	thread = new Thread(fptr, nullptr);
	timer = new Timer();
	thread->run(fptr, nullptr);
}

TaskScheduler::~TaskScheduler()
{
	thread->join();
	thread->close();
	delete thread;
	delete timer;
}

void TaskScheduler::loop()
{
	while (1) {
		timer->msWait(interval);
		callcack(nullptr);
	}
}
