#include "TaskScheduler.hh"

TaskScheduler::TaskScheduler(Callback_t _callback, long _t)
{
	callcack = _callback;
	interval = _t;
	timer = new Timer();
	running = true;
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
	while (running) {
		timer->msWait(interval);
		callcack(nullptr);
	}
}

void TaskScheduler::stop()
{
	running = false;
}
