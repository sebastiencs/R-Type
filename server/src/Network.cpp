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
  : _sem(new Semaphore),
    _socket(new SocketUDP(SocketUDP::SERVER)),
    _selector(new Selector(this)),
    _thread(new Thread([this](void *) -> void * { write(); return (0);}, 0))
{
  DEBUG_MSG("Network created");
  _socket->bind(port);
}

Network::~Network()
{
  DEBUG_MSG("Network deleted");
  _thread->close();
}

int	Network::run()
{
  _running = true;

  while (_running) {

    ssize_t	size;

    size = _socket->read(_buffer);

    if (size > 0) {
      _selector->execFunc(_buffer);
    }
  }
  return (0);
}

int	Network::stop()
{
  _running = false;
  return (0);
}

bool	Network::write(const Paquet &paquet, const Addr &addr)
{
  PaquetClient	pc;

  pc.paquet = paquet;
  pc.addr = addr;

  _stackPaquet.push(pc);
  _sem->post();
  return (true);
}

bool	Network::write()
{
  for (;;) {
    _sem->wait();

    if (_stackPaquet.size()) {

      PaquetClient pc = _stackPaquet.top();

      if (_socket->write(pc.paquet, pc.addr) >= 0) {
	_stackPaquet.pop();
      }
      else {
	_sem->post();
      }
    }
  }
  return (true);
}

int	Network::handleFirst(PaquetFirst paquet)
{
  PaquetFirst	p;

  p.setVersion(1);
  p.setName("seb");
  p.setLevel(1);
  p.createPaquet();

  write(p, _socket->getAddr());

  DEBUG_MSG(paquet);
  return (0);
}
