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
    _socketUDP(new SocketUDP(SocketUDP::SERVER)),
    _socketTCP(new SocketTCP(SocketTCP::SERVER)),
    _selector(new Selector(this)),
    _thread(new Thread([this](void *) -> void * { write(); return (0);}, 0))
{
  DEBUG_MSG("Network created");
  _socketUDP->bind(port);
  _socketTCP->bind(port);
  _socketTCP->listen(0x200);
}

Network::~Network()
{
  DEBUG_MSG("Network deleted");
  _thread->close();
}

#include <set>

int	Network::run()
{
  _running = true;

  Pollfd	fds(2);

  fds[0].fd = _socketTCP->socket();
  fds[0].events = POLLIN;
  fds[1].fd = _socketUDP->socket();
  fds[1].events = POLLIN;

  while (_running) {

    if (poll(fds.data(), fds.size(), 0) > 0) {

      for (auto fd : fds) {
	if (fd.revents & POLLIN) {

	  if (fd.fd == _socketUDP->socket()) {

	    ssize_t size = _socketUDP->read(_buffer);

	    if (size > 0) {
	      _selector->execFunc(_buffer);
	    }
	    break ;
	  }
	  else if (fd.fd == _socketTCP->socket()) {

	    DEBUG_MSG("New client TCP");

	    ISocketTCP *sock = _socketTCP->accept();
	    _socketClient.push_back(sock);

	    size_t	size_fds = fds.size();
	    fds.resize(size_fds + 1);
	    fds[size_fds - 1].fd = sock->socket();
	    fds[size_fds - 1].events = POLLIN;

	    ssize_t	size;
	    size = sock->read(_buffer);
	    std::cout << "SIZE: " << size << std::endl;
	    break ;
	  }
	  else {

	    for (auto fd_client : _socketClient) {

	      if (fd_client->socket() == fd.fd) {

		ssize_t	size;
		size = fd_client->read(_buffer);

		std::cout << "SIZE: " << (int)size << std::endl;

		if (size <= 0) {

		  std::cerr << "Client disconnect\n";

		  socket_t fdc = fd.fd;
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
	  }
	}
      }
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

      if (_socketUDP->write(pc.paquet, pc.addr) >= 0) {
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

  write(p, _socketUDP->getAddr());

  DEBUG_MSG(paquet);
  return (0);
}
