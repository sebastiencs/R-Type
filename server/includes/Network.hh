//
// Network.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 10 22:59:35 2015 chapui_s
// Last update Tue Nov 10 22:59:35 2015 chapui_s
//

#ifndef NETWORK_H_
# define NETWORK_H_

# include <iostream>
# include <memory>
# include <map>
# include <functional>
# include <queue>
# include "Socket.hh"
# include "Debug.hh"
# include "Paquets.hh"
# include "INetwork.hh"
# include "Thread.hh"
# include "Semaphore.hh"
# include "IOEvent.hh"
# include "QueueSecure.hh"

class	Selector;
class	Manager;

typedef std::unique_ptr<Selector>	Selector_UniquePtr;

typedef std::weak_ptr<Manager>		Manager_WeakPtr;
typedef std::shared_ptr<Manager>	Manager_SharedPtr;

typedef struct	s_paquet_client
{
  Paquet	paquet;
  Addr		addr;
  s_paquet_client(const Paquet &p, const Addr &a)
    : paquet(p), addr(a) { }
}		PaquetClient;

typedef std::shared_ptr<PaquetClient>	PaquetClient_SharedPtr;

class				Network
  : public INetwork
{
private:

  ISemaphore_UniquePtr		_sem;
  ISocketUDP_UniquePtr		_socketUDP;
  ISocketTCP_UniquePtr		_socketTCP;
  Selector_UniquePtr		_selector;
  bool				_running;
  IThread_UniquePtr		_thread;
  QueueSecure<PaquetClient_SharedPtr>	_queuePaquet;
  std::list<ISocketTCP_SharedPtr>	_socketClient;
  Manager_WeakPtr		_manager;
  Buffer			_buffer;

public:
  Network(const Manager_SharedPtr &&, const uint16_t);
  virtual ~Network();

  virtual int	run();
  virtual int	stop();

  virtual bool	write(const Paquet &, const Addr &);
  virtual bool	write();

  bool		handleUDP();
  bool		handleNewTCP(Pollfd &fds);
  bool		handleTCP(const socket_t socket, Pollfd &fds);
};

#endif /* !NETWORK_H_ */
