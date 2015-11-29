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

SignalWin::SignalWin(Server &server)
	: _server(server)
{
	DEBUG_MSG("SignalUnix created");
	class_save(1, this);
}

SignalWin::~SignalWin()
{
	DEBUG_MSG("SignalUnix deleted");
}

void		SignalWin::addSignal(int sig)
{
	(void)sig;
}

void		SignalWin::stopAll()
{
	DEBUG_MSG("SignalUnix received");
	_server.stop();
}

SignalWin		*class_save(int id, SignalWin *ptr_class)
{
	static SignalWin	*signal = 0;

	if (!id) {
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

	(void)sig;
	signal = class_save(0, 0);
	if (signal) {
		signal->stopAll();
	}
}
