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

  int reconnect();

  virtual int	handleFirst(PaquetFirst);

  template <class T>
  bool	writeUDP(const T &input, const Addr &addr) {
    if ((_socketUDP->write(input, addr)) == 0)
      return true;
    return false;
  }

  template <class T>
  bool	writeTCP(const T &input) {
    if ((_socketTCP->write(input)) == 0)
      return true;
    return false;
  }
  bool getIsConnect();
  void setInGame(bool _inGame);

private:

  ISocketUDP*	_socketUDP;
  ISocketTCP*	_socketTCP;

  Thread*	threadWrite;
  Thread*	threadRead;

  std::string _ip;
  int _port;

  bool inGame;
  bool _isConnect;
};

#endif /* !NETWORKCLIENT_H_ */
