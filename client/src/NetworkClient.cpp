#include <NetworkClient.hh>

NetworkClient::NetworkClient(const std::string& ip, const uint16_t port)
  : _socketUDP(new SocketUDP(SocketUDP::CLIENT)),
    _socketTCP(new SocketTCP(SocketTCP::CLIENT))
{
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
  _socketTCP->write(first);
  DEBUG_MSG(first);
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
