#ifndef NETWORKCLIENT_H_
# define NETWORKCLIENT_H_

# include <iostream>
# include "Socket.hh"
# include "Debug.hh"
# include "Paquets.hh"
# include "Thread.hh"


class				NetworkClient
{
private:

  ISocketUDP*	_socketUDP;
  ISocketTCP*	_socketTCP;

public:
  NetworkClient(const std::string&, const uint16_t);
  virtual ~NetworkClient();

  virtual int	run();
  virtual int	stop();

  virtual int	handleFirst(PaquetFirst);
  virtual bool	writeUDP(const Buffer &, const Addr &);
  virtual bool	writeTCP(const Buffer &);
};

#endif /* !NETWORKCLIENT_H_ */