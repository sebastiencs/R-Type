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
#include "Manager.hh"
#include "IOEvent.hh"
#include "Tools.hh"
#include "PaquetTCP.hh"

Network::Network(const Manager_SharedPtr &&manager, const uint16_t port)
  : _sem(std::make_unique<Semaphore>()),
    _socketUDP(std::make_unique<SocketUDP>(SocketUDP::SERVER)),
    _socketTCP(std::make_unique<PaquetTCP>(SocketTCP::SERVER)),
    _selector(std::make_unique<Selector>(std::move(manager))),
    _running(true),
    _thread(std::make_unique<Thread>([this](void *) -> void * { write(); return (0);}, nullptr)),
    _manager(std::move(manager))
{
  DEBUG_MSG("Network created");
  _socketUDP->bind(port);
  _socketTCP->bind(port);
  _socketTCP->listen(0x200);
}

Network::~Network()
{
  _thread->close();
  DEBUG_MSG("Network deleted");
}

int	Network::run()
{
  (_manager.lock())->setNetwork(shared_from_this());

  Pollfd	fds(2);

  fds[0].fd = _socketTCP->socket();
  fds[0].events = POLLIN;
  fds[1].fd = _socketUDP->socket();
  fds[1].events = POLLIN;

  while (_running) {

    if (IOEvent::poll(fds, IOEvent::POLL_WAIT) > 0) {

      for (auto &fd : fds) {
	if (fd.revents & POLLIN) {
	  if (fd.fd == _socketUDP->socket()) {
	    handleUDP();
	    break ;
	  }
	  else if (fd.fd == _socketTCP->socket()) {
	    handleNewTCP(fds);
	    break ;
	  }
	  else {
	    handleTCP(fd.fd, fds);
	    break ;
	  }
	}
      }
    }
  }
  return (0);
}

inline bool	Network::handleUDP()
{
  ssize_t size = _socketUDP->read(_buffer);

  if (size > 0) {
    _selector->execFunc(_buffer, _socketUDP->getAddr());
  }
  return (true);
}

inline bool	Network::handleNewTCP(Pollfd &fds)
{
  DEBUG_MSG("New client TCP");

  ISocketTCP	*sock = _socketTCP->accept();
  _socketClient.push_back(ISocketTCP_SharedPtr(sock));

  size_t	size_fds = fds.size();
  fds.resize(size_fds + 1);
  fds[size_fds].fd = sock->socket();
  fds[size_fds].events = POLLIN;

  return (true);
}

inline bool	Network::handleTCP(const socket_t socket, Pollfd &fds)
{

  auto sock = Tools::findIn(_socketClient, [&socket] (auto &sock) { return (sock->socket() == socket); });
  ssize_t size;

  try {
    size = sock->read(_buffer);
  }
  catch (Disconnected &) {
    DEBUG_MSG("Client disconnect\n");
    (_manager.lock())->deletePlayer(socket);

    auto it = Tools::findIt(fds, [&socket] (auto &fd) { return (fd.fd == socket); });
    if (it != fds.end()) {
      fds.erase(it);
    }
    _socketClient.remove(sock);
  }

  if (size > 0) {
    DEBUG_MSG(_buffer);
    _selector->execFunc(_buffer, sock->getAddr());
  }
  return (true);
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

  _queuePaquet.push(pc);
  _sem->post();
  return (true);
}

bool	Network::write()
{
  while (_running) {
    _sem->wait();

    if (_queuePaquet.size()) {

      PaquetClient pc = _queuePaquet.front();

      if (pc.paquet.getType() == Paquet::UDP) {
	if (_socketUDP->write(pc.paquet, pc.addr) >= 0) {
	  _queuePaquet.pop();
	}
	else {
	  _sem->post();
	}
      }
      else {
	if (_socketTCP->write(pc.paquet, pc.addr) >= 0) {
	  _queuePaquet.pop();
	}
	else {
	  std::cout << "write failed" << std::endl;
	  _sem->post();
	}
      }
    }
  }
  return (true);
}
