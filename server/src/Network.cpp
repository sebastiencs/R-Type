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

Network::Network(const uint16_t port)
  : _socket(new SocketUDP(SocketUDP::SERVER)),
    _running(true)
{
  DEBUG_MSG("Network created");
  _socket->bind(port);

  _paquetFunc[Paquet::FIRST] = [this](ssize_t size) -> int { return (manageFirst(PaquetFirst(_buffer, size))); };
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

    auto func = _paquetFunc.find(_buffer[0]);
    if (func != _paquetFunc.end()) {
      func->second(size);
    }
  }
  return (0);
}

int	Network::stop()
{
  _running = false;
  return (0);
}

int	Network::manageFirst(PaquetFirst paquet)
{
  std::cout << paquet << std::endl;
  return (0);
}
