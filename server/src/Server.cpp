//
// Server.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 10 22:39:14 2015 chapui_s
// Last update Tue Nov 10 22:39:14 2015 chapui_s
//

#include "Server.hh"

Server::Server(const uint16_t port)
  : _manager(std::make_shared<Manager>()),
    _network(std::make_shared<Network>(_manager->getPtr(), port)),
    _signal(std::make_unique<Signal>())
{
  _signal->addSignal(CTRL_C, [this]() -> void { stop(); });
  DEBUG_MSG("Server created");
}

Server::~Server()
{
  DEBUG_MSG("Server deleted");
}

int	Server::run()
{
  return (_network->run());
}

int	Server::stop()
{
  return (_network->stop());
}
