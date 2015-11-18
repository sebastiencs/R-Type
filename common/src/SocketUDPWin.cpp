//
// SocketUDPWin.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 15:45:54 2015 chapui_s
// Last update Wed Nov 11 15:45:54 2015 chapui_s
//

#include <stdexcept>
#include "SocketUDPWin.hh"

SocketUDPWin::SocketUDPWin(CONNECTION_TYPE type)
  : _isKnown(false),
    _type(type)
{
  if (type == SERVER)
  {
	  if ((_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
  		DEBUG_MSG("SockectUDPWin failed : " + WSAGetLastError());
	  else
	  	DEBUG_MSG("SocketUDPWin created");
  }
  else if (type == CLIENT)
  {
	  if ((_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
  		DEBUG_MSG("SockectUDPWin failed : " + WSAGetLastError());
	  else
	  	DEBUG_MSG("SocketUDPWin created");
  }
}

SocketUDPWin::SocketUDPWin(CONNECTION_TYPE type, socket_t fd)
  : _isKnown(false)
{
	_socket = fd;
	if (_socket == INVALID_SOCKET)
		DEBUG_MSG("SockectUDPWin failed : ");
	else
		DEBUG_MSG("SocketUDPWin created");
}

SocketUDPWin::~SocketUDPWin()
{
  closesocket(_socket);
  DEBUG_MSG("SocketUDPWin deleted");
}

int	SocketUDPWin::connect(const std::string &addr, uint16_t port)
{
  // For the Client
  _client.sin_family = AF_INET;
  _client.sin_port = htons(port);
  inet_pton(AF_INET, addr.c_str(), (PVOID *)(&_client.sin_addr.S_un.S_addr));
  //_client.sin_addr.S_un.S_addr = inet_addr(addr.c_str());
	return (0);
}

int	SocketUDPWin::bind(uint16_t port)
{
  // For the Server
  _server.sin_family = AF_INET;
	_server.sin_addr.s_addr = INADDR_ANY;
	_server.sin_port = htons(port);
	if (::bind(_socket, (struct sockaddr *)&_server, sizeof(_server)) == SOCKET_ERROR)
		DEBUG_MSG("Bind failed");
	else
		DEBUG_MSG("Bind done");
	return (0);
}

ssize_t	SocketUDPWin::write(const Buffer &buf)
{
  ssize_t	n;

  if (_type == SocketUDPWin::SERVER) {
    if (_isKnown == false) {
      throw std::runtime_error("Error sendto() client unknown");
    }
    n = sendto(_socket, (const char *)buf.get(), buf.size(), 0, (struct sockaddr *) &_client, _clientLen);
  }
  else {
    n = sendto(_socket, (const char *)buf.get(), buf.size(), 0, (struct sockaddr *) &_server, sizeof(_server));
  }
  if (n == SOCKET_ERROR) {
    DEBUG_MSG("Sendto failed: " + WSAGetLastError());
    n = -1;
  }
  return (n);
}

ssize_t	SocketUDPWin::write(const Buffer &buf, const Addr &addr)
{
  struct sockaddr_in	addrIn = addr.get();
  ssize_t		n;

  if ((n = sendto(_socket, (const char *)buf.get(), buf.size(), 0, (struct sockaddr *) &addrIn, sizeof(addrIn))) == SOCKET_ERROR) {
      DEBUG_MSG("Sendto failed: " + WSAGetLastError());
      n = -1;
  }
  return (n);
}

ssize_t	SocketUDPWin::read(Buffer &buf)
{
  Buffer	tmp;
  int		recvlen = 0;

  if (_type == SocketUDPWin::SERVER) {
    recvlen = recvfrom(_socket, (char *)tmp.get(), tmp.size(), 0, (struct sockaddr *) &_client, &_clientLen);
    if (recvlen >= 0) {
      _isKnown = true;
    }
  }
  else {
    recvlen = recvfrom(_socket, (char *)tmp.get(), tmp.size(), 0, (struct sockaddr *) &_server, &_clientLen);
  }
  if (recvlen = SOCKET_ERROR) {
    DEBUG_MSG("RecvFrom failed: " + WSAGetLastError());
  }
  else {
    tmp.setSize(recvlen);
    buf = tmp;
  }
  return (recvlen);
}


const Addr	SocketUDPWin::getAddr() const
{
  return (Addr(_client));
}
