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
  : _isKnown(false)
{
  if (type == SERVER)
  {
	  if ((_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
		DEBUG_MSG("SockectUDPWin failed : " + WSAGetLastError());
	  else
		DEBUG_MSG("SocketUDPWin created");
  }
}

SocketUDPWin::SocketUDPWin(CONNECTION_TYPE type, socket_t fd)
  : _isKnown(false)
{
	if (type == SERVER)
	{
		_socket = fd;
		if (_socket == INVALID_SOCKET)
			DEBUG_MSG("SockectUDPWin failed : ");
		else
			DEBUG_MSG("SocketUDPWin created");
	}
}

SocketUDPWin::~SocketUDPWin()
{
  closesocket(_socket);
  DEBUG_MSG("SocketUDPWin deleted");
}

int	SocketUDPWin::connect(const std::string &addr, uint16_t port)
{
	return (0);
}

int	SocketUDPWin::bind(uint16_t port)
{
	_server.sin_family = AF_INET;
	_server.sin_addr.s_addr = INADDR_ANY;
	_server.sin_port = htons(port);
	if (bind((_socket, (struct sockaddr *)&_server, sizeof(_server))) == SOCKET_ERROR)
		DEBUG_MSG("Bind failed");
	else
		DEBUG_MSG("Bind done");
	return (0);
}

ssize_t	SocketUDPWin::write(const void * data, size_t len)
{
  // Ici on a pas le client a qui on envoit les info ... j'ai fait qqch de temporaire
  if (_isKnown == false) {
    throw std::runtime_error("Error sendto() client unknown");
  }
  if ((sendto(_socket, (const char *)data, len, 0, (struct sockaddr *) &_client, _clientLen)) == SOCKET_ERROR)
      DEBUG_MSG("Sendto failed: " + WSAGetLastError());
  return (0);
}

ssize_t	SocketUDPWin::read(void *data, size_t len)
{
  int recvlen = 0;
  // Ici il faudrai recuperer les clients, et les stocker dans une classe "conteneur" de client
  if ((recvlen = recvfrom(_socket, (char *)data, len, 0, (struct sockaddr *) &_client, &_clientLen)) == SOCKET_ERROR)
      DEBUG_MSG("RecvFrom failed: " + WSAGetLastError());
  else {
      _isKnown = true;
      DEBUG_MSG((char *)data);
  }
  return (recvlen);
}
