#include <NetworkClient.hh>

NetworkClient::NetworkClient(const std::string& ip, const uint16_t port)
  : _socketTCP(new SocketTCP(SocketTCP::CLIENT)),
    _socketUDP(new SocketUDP(SocketUDP::CLIENT))

{
  DEBUG_MSG(_socketTCP->bind(port));
  _socketUDP->bind(port);
  _socketTCP->connect(ip, port);
}

NetworkClient::~NetworkClient()
{
  DEBUG_MSG("NetworkClient deleted");
}

int NetworkClient::run()
{
  return 0;
}

int NetworkClient::stop()
{
  return 0;
}

int NetworkClient::handleFirst(PaquetFirst first)
{
  /* Test */
  PaquetFirst	p;

  p.setVersion(1);
  p.setName("Alex");
  p.setLevel(1);
  p.createPaquet();
  Buffer buff(p.getData(), p.getSize());
  /* !Test*/

  _socketTCP->write(buff);

  DEBUG_MSG(paquet);
  return 0;
}

bool NetworkClient::writeUDP(const Buffer& buf, const Addr& addr)
{
  if ((_socketUDP->write(buf, addr)) == 0)
    return true;
  return false;
}

bool NetworkClient::writeTCP(const Buffer& buf)
{
  if ((_socketTCP->write(buf)) == 0)
    return true;
  return false;
}
