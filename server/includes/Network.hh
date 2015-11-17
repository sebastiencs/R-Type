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
# include "Socket.hh"
# include "Debug.hh"
# include "Paquets.hh"

class	Selector;

class				Network
{
private:

  std::unique_ptr<ISocketUDP>	_socket;
  bool				_running;
  Buffer			_buffer;
  std::unique_ptr<Selector>	_selector;

public:
  Network(const uint16_t);
  virtual ~Network();

  virtual int	run();
  virtual int	stop();

  virtual int	handleFirst(PaquetFirst);
};

#endif /* !NETWORK_H_ */
