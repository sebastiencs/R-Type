//
// SignalWin.cpp for epitech in /home/bresci_b/R-Type
//
// Made by bresci_b
// Login   <bresci_b@epitech.eu>
//
// Started on  Sun Nov 29 18:46:32 2015 bresci_b
// Last update Sun Nov 29 18:46:32 2015 bresci_b
//

#include "SignalWin.hh"

SignalWin::SignalWin()
{
	DEBUG_MSG("SignalWin created");
	class_save(this);
}

SignalWin::~SignalWin()
{
	DEBUG_MSG("SignalWin deleted");
}

void		SignalWin::addSignal(int sig, Handler_t handler)
{
	//signal(sig, sig_handler);
	_listHandler[sig] = handler;
}

void		SignalWin::callHandler(int sig)
{
	DEBUG_MSG("SignalWin received");
	if (_listHandler.find(sig) != _listHandler.end()) {
		_listHandler[sig]();
	}
}

SignalWin		*class_save(SignalWin *ptr_class = nullptr)
{
	static SignalWin	*signal = nullptr;

	if (ptr_class == nullptr) {
		return (signal);
	}
	else {
		signal = ptr_class;
		return (signal);
	}
}

void		sig_handler(int sig)
{
	SignalWin	*signal;

	signal = class_save();
	if (signal) {
		signal->callHandler(sig);
	}
}

