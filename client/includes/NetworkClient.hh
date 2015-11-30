#ifndef NETWORKCLIENT_H_
# define NETWORKCLIENT_H_

# include <iostream>
# include "Socket.hh"
# include "Debug.hh"
# include "Paquets.hh"
# include "Thread.hh"
# include "IOEvent.hh"
# include "PackagerTranslator.hh"
# include "PackageStorage.hh"


class				NetworkClient
{

public:
  NetworkClient(const std::string&, const uint16_t);
  virtual ~NetworkClient();

  virtual int	runWrite();
  virtual int	runRead();
  virtual int	stop();

  virtual int	handleFirst(PaquetFirst);
  virtual bool	writeUDP(const Buffer &, const Addr &);
  virtual bool	writeTCP(const Buffer &);
  void setInGame(bool _inGame);

private:

  ISocketUDP*	_socketUDP;
  ISocketTCP*	_socketTCP;

  Thread*	threadWrite;
  Thread*	threadRead;

  bool inGame;
  bool _isConnect;
};

#endif /* !NETWORKCLIENT_H_ */
