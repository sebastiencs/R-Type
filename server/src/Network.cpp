//
// Network.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 10 22:59:58 2015 chapui_s
// Last update Tue Nov 10 22:59:58 2015 chapui_s
//

#include "Network.hh"
#include "Selector.hh"

Network::Network(const uint16_t port)
  : _socket(new SocketUDP(SocketUDP::SERVER)),
    _running(true),
    _selector(new Selector(this))
{
  DEBUG_MSG("Network created");
  _socket->bind(port);
}

Network::~Network()
{
  DEBUG_MSG("Network deleted");
}

int	Network::run()
{
  while (_running) {

    ssize_t	size;

    size = _socket->read(_buffer, sizeof(_buffer));

    _selector->execFunc(_buffer, size);
  }
  return (0);
}

int	Network::stop()
{
  _running = false;
  return (0);
}

int	Network::handleFirst(PaquetFirst paquet)
{
  DEBUG_MSG(paquet);
  return (0);
}
