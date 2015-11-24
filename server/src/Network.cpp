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

Network::Network(Manager *manager, const uint16_t port)
  : _sem(new Semaphore),
    _socketUDP(new SocketUDP(SocketUDP::SERVER)),
    _socketTCP(new SocketTCP(SocketTCP::SERVER)),
    _selector(new Selector(manager)),
    _thread(new Thread([this](void *) -> void * { write(); return (0);}, 0)),
    _manager(manager)
{
  DEBUG_MSG("Network created");
  _socketUDP->bind(port);
  _socketTCP->bind(port);
  _socketTCP->listen(0x200);
  _manager->setNetwork(this);
}

Network::~Network()
{
  DEBUG_MSG("Network deleted");
  _thread->close();
}

int	Network::run()
{
  _running = true;

  Pollfd	fds(2);

  fds[0].fd = _socketTCP->socket();
  fds[0].events = POLLIN;
  fds[1].fd = _socketUDP->socket();
  fds[1].events = POLLIN;

  while (_running) {

    if (IOEvent::poll(fds, 0) > 0) {

      for (auto fd : fds) {
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
  DEBUG_MSG("UDP socket");

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
  _socketClient.push_back(sock);

  size_t	size_fds = fds.size();
  fds.resize(size_fds + 1);
  fds[size_fds - 1].fd = sock->socket();
  fds[size_fds - 1].events = POLLIN;

  ssize_t	size;
  size = sock->read(_buffer);
  std::cout << "SIZE: " << size << std::endl;
  if (size > 0) {
    _selector->execFunc(_buffer, sock->getAddr());
  }
  return (true);
}

inline bool	Network::handleTCP(const socket_t socket, Pollfd &fds)
{
  for (auto fd_client : _socketClient) {

    if (fd_client->socket() == socket) {

      ssize_t	size;
      size = fd_client->read(_buffer);

      std::cout << "SIZE: " << (int)size << std::endl;

      if (size > 0) {
	_selector->execFunc(_buffer, fd_client->getAddr());
      }
      else {

	std::cerr << "Client disconnect\n";

	socket_t fdc = socket;

	_manager->deletePlayer(fdc);
	for (auto it = fds.cbegin(); it != fds.cend(); ++it) {
	  if ((*it).fd == fdc) {
	    fds.erase(it);
	    break ;
	  }
	}
	_socketClient.remove(fd_client);
	break ;
      }
    }
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

      if (pc.addr.getType() == Addr::UDP) {
	if (_socketUDP->write(pc.paquet, pc.addr) >= 0) {
	  _stackPaquet.pop();
	}
	else {
	  _sem->post();
	}
      }
      else {
	if (_socketTCP->write(pc.paquet, pc.addr) >= 0) {
	  _stackPaquet.pop();
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
