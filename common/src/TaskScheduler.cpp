#include "TaskScheduler.hh"

TaskScheduler::TaskScheduler(Callback_t _callback, long _t)
{
	callcack = _callback;
	interval = _t;
	timer = new Timer();
	running = true;
	fptr = [this](void *) {this->loop(); return nullptr; };
	run();
}

TaskScheduler::~TaskScheduler()
{
	if (timer)
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
	// thread->close(); // Can't close our own thread -> segfault
	// delete thread;
	thread = nullptr;
}

void TaskScheduler::run()
{
	thread = new Thread(fptr, nullptr);
	thread->run(fptr, nullptr);
}
