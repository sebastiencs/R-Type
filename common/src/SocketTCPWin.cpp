//
// SocketTCPWin.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 15:43:03 2015 chapui_s
// Last update Wed Nov 11 15:43:03 2015 chapui_s
//

#include <stdexcept>
#include "SocketTCPWin.hh"

SocketTCPWin::SocketTCPWin(CONNECTION_TYPE type)
{
  if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    DEBUG_MSG("SockectTCOWin failed : " + WSAGetLastError());
  else
    DEBUG_MSG("SocketTCPWin created");
}

SocketTCPWin::SocketTCPWin(CONNECTION_TYPE type,
			     socket_t fd)
{
  _socket = fd;
  if (_socket == INVALID_SOCKET)
    DEBUG_MSG("SockectTCPWin failed : ");
  else
    DEBUG_MSG("SocketTCPWin created");
}

SocketTCPWin::~SocketTCPWin()
{
  closesocket(_socket);
  DEBUG_MSG("SocketTCPWin deleted");
}

int	SocketTCPWin::connect(const std::string &addr, uint16_t port)
{
  _client.sin_family = AF_INET;
  _client.sin_addr.s_addr = inet_addr(addr.c_str());
  _client.sin_port = htons(port);
  if (::connect(_socket, (struct sockaddr *)&_client, sizeof(_client)) == INVALID_SOCKET) {
    DEBUG_MSG("Connect failed");
  }
  return (0);
}

ISocketTCP	*SocketTCPWin::accept()
{
  socket_t socket;
  int tmp = sizeof(_server);

  if ((socket = ::accept(_socket, (struct sockaddr *)&_server, &tmp)) == INVALID_SOCKET) {
    DEBUG_MSG("Accept failed");
    return (0);
  }
  DEBUG_MSG("Accept done"); 
  SocketTCPWin* newClient = new SocketTCPWin(CLIENT, socket);
  return newClient;
}

int	SocketTCPWin::bind(uint16_t port)
{
  _server.sin_family = AF_INET;
  _server.sin_addr.s_addr = INADDR_ANY;
  _server.sin_port = htons(port);
  if (::bind(_socket, (struct sockaddr *)&_server, sizeof(_server)) == SOCKET_ERROR)
    DEBUG_MSG("Bind failed");
  else
    DEBUG_MSG("Bind done");
  return (0);
}

int	SocketTCPWin::listen(int max)
{
  ::listen(_socket, max);
  return (0);
}

ssize_t	SocketTCPWin::write(const Buffer &buf)
{
  if ((send(_socket, (const char *)buf.get(), buf.size(), 0)) == SOCKET_ERROR) {
    DEBUG_MSG("Send failed: " + WSAGetLastError());
  }
  return (0);
}

ssize_t	SocketTCPWin::read(Buffer &buf)
{
  int recvlen = 0;
  if ((recvlen = recv(_socket, (char *)buf.get(), buf.size(), 0)) == SOCKET_ERROR)
    DEBUG_MSG("Recv failed: " + WSAGetLastError());
  else {
    DEBUG_MSG((char *)data);
  }
  return (recvlen);
}
