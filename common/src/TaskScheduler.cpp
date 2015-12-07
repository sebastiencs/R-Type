#include "TaskScheduler.hh"

TaskScheduler::TaskScheduler(Callback_t _callback, long _t)
{
	callcack = _callback;
	interval = _t;
	timer = new Timer();
	Callback_t fptr = [this](void *) {this->loop(); return nullptr; };
	thread = new Thread(fptr, nullptr);
	thread->run(fptr, nullptr);
}

TaskScheduler::~TaskScheduler()
{
	thread->close();
	delete thread;
	delete timer;
}

void TaskScheduler::loop()
{
	timer->start();
	while (1) {
		timer->msWait(interval);
		callcack(nullptr);
		timer->reset();
	}
}
