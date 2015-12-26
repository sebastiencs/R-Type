//
// SignalUnix.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 29 18:49:03 2015 chapui_s
// Last update Sun Nov 29 18:49:03 2015 chapui_s
//

#include <iostream>
#include <signal.h>
#include "Debug.hh"
#include "SignalUnix.hh"

SignalUnix::SignalUnix()
{
  DEBUG_MSG("SignalUnix created");
  class_save(this);
}

SignalUnix::~SignalUnix()
{
  DEBUG_MSG("SignalUnix deleted");
}

void		SignalUnix::addSignal(const int sig, const Handler_t &&handler)
{
  signal(sig, sig_handler);
  _listHandler[sig] = handler;
}

bool		SignalUnix::callHandler(const int sig)
{
  DEBUG_MSG("SignalUnix received");
  if (_listHandler.find(sig) != _listHandler.end()) {
    _listHandler[sig]();
    return (true);
  }
  return (false);
}

SignalUnix		*class_save(SignalUnix *ptr_class = nullptr)
{
  static SignalUnix	*signal = nullptr;

  if (ptr_class == nullptr) {
    return (signal);
  }
  else {
    signal = ptr_class;
    return (signal);
  }
}

void		sig_handler(const int sig)
{
  SignalUnix	*signal;

  signal = class_save();
  if (signal) {
    signal->callHandler(sig);
  }
}
