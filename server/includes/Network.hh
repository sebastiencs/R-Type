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

class	Selector;

//typedef std::tuple<Paquet *, Addr>	PaquetClient;

typedef struct	s_paquet_client
{
  Paquet	paquet;
  Addr		addr;
}		PaquetClient;

class				Network : public INetwork
{
private:

  std::unique_ptr<Semaphore>	_sem;
  std::unique_ptr<ISocketUDP>	_socket;
  std::unique_ptr<Selector>	_selector;
  std::unique_ptr<IThread>	_thread;
  std::stack<PaquetClient>	_stackPaquet;
  bool				_running;
  Buffer			_buffer;

public:
  Network(const uint16_t);
  virtual ~Network();

  virtual int	run();
  virtual int	stop();

  virtual int	handleFirst(PaquetFirst);
  virtual bool	write(const Paquet &, const Addr &);
  virtual bool	write();
};

#endif /* !NETWORK_H_ */
