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
  : _port(port)
{
  DEBUG_MSG("Network created");
}

Network::~Network()
{
  DEBUG_MSG("Network deleted");
}
