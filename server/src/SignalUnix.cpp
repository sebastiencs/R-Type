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
#include "Server.hh"

SignalUnix::SignalUnix(Server &server)
  : _server(server)
{
  DEBUG_MSG("SignalUnix created");
  class_save(1, this);
}

SignalUnix::~SignalUnix()
{
  DEBUG_MSG("SignalUnix deleted");
}

void		SignalUnix::addSignal(int sig)
{
  signal(sig, sig_handler);
}

void		SignalUnix::stopAll()
{
  DEBUG_MSG("SignalUnix received");
  _server.stop();
}

SignalUnix		*class_save(int id, SignalUnix *ptr_class)
{
  static SignalUnix	*signal = 0;

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
  SignalUnix	*signal;

  (void)sig;
  signal = class_save(0, 0);
  if (signal) {
    signal->stopAll();
  }
}
