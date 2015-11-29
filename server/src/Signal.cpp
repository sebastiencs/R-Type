//
// Signal.cpp<R-Type> for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 29 16:36:16 2015 chapui_s
// Last update Sun Nov 29 16:36:16 2015 chapui_s
//

#include <iostream>
#include <signal.h>
#include "Debug.hh"
#include "Signal.hh"
#include "Server.hh"

Signal::Signal(Server &server)
  : _server(server)
{
  DEBUG_MSG("Signal created");
  class_save(1, this);
}

Signal::~Signal()
{
  DEBUG_MSG("Signal deleted");
}

void		Signal::addSignal(int sig)
{
  signal(sig, sig_handler);
}

void		Signal::stopAll()
{
  DEBUG_MSG("Signal received");
  _server.stop();
}

Signal		*class_save(int id, Signal *ptr_class)
{
  static Signal	*signal = 0;

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
  Signal	*signal;

  (void)sig;
  signal = class_save(0, 0);
  if (signal) {
    signal->stopAll();
  }
}
