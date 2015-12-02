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
# include <stack>
# include "Socket.hh"
# include "Debug.hh"
# include "Paquets.hh"
# include "INetwork.hh"
# include "Thread.hh"
# include "Semaphore.hh"
# include "IOEvent.hh"

class	Selector;
class	Manager;

typedef struct	s_paquet_client
{
  Paquet	paquet;
  Addr		addr;
}		PaquetClient;

class				Network
  : public INetwork,
    public std::enable_shared_from_this<Network>
{
private:

  std::unique_ptr<Semaphore>	_sem;
  std::unique_ptr<ISocketUDP>	_socketUDP;
  std::unique_ptr<ISocketTCP>	_socketTCP;
  std::unique_ptr<Selector>	_selector;
  bool				_running;
  std::unique_ptr<IThread>	_thread;
  std::stack<PaquetClient>	_stackPaquet;
  std::list<ISocketTCP *>	_socketClient;
  std::weak_ptr<Manager>	_manager;
  Buffer			_buffer;

public:
  Network(std::shared_ptr<Manager>, const uint16_t);
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
