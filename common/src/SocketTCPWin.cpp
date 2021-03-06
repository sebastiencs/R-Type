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

SocketTCPWin::SocketTCPWin(const CONNECTION_TYPE type)
{
  _type = type;
  if ((_socket = ::socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    DEBUG_MSG("SockectTCOWin failed : " << WSAGetLastError());
  else
    DEBUG_MSG("SocketTCPWin created");
}

SocketTCPWin::SocketTCPWin(const CONNECTION_TYPE type,
			   const socket_t fd,
			   struct sockaddr_in &addr,
			   const uint16_t port)
  : _socket(fd),
    _addr(fd, addr, port),
    _port(port),
    _type(type)
{
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

socket_t	SocketTCPWin::socket() const
{
  return (_socket);
}

int	SocketTCPWin::connect(const std::string &addr, const uint16_t port)
{
  if (_type == SocketTCPWin::SERVER) {
    throw std::runtime_error("Try to connect with a server");
  }
  _addr.get().sin_family = AF_INET;
  inet_pton(AF_INET, addr.c_str(), (PVOID *)(&_addr.get().sin_addr.s_addr));
  //_client.sin_addr.s_addr = inet_addr(addr.c_str());
  _addr.get().sin_port = htons(port);
  if (::connect(_socket, (struct sockaddr *)&_addr.get(), sizeof(_addr.get())) == INVALID_SOCKET) {
    DEBUG_MSG("Connect failed");
	return (-1);
  }
  return (0);
}

ISocketTCP	*SocketTCPWin::accept()
{
  socket_t socket;
  struct sockaddr_in	c_addr;
  int tmp = sizeof(c_addr);

  if (_type == SocketTCPWin::CLIENT) {
    throw std::runtime_error("Try to connect with a server");
  }
  if ((socket = ::accept(_socket, (struct sockaddr *)&c_addr, &tmp)) == INVALID_SOCKET) {
    DEBUG_MSG("Accept failed");
    return (0);
  }
  DEBUG_MSG("Accept done");
  SocketTCPWin* newClient = new SocketTCPWin(CLIENT, socket, c_addr, _port);
  return newClient;
}

int	SocketTCPWin::bind(const uint16_t port)
{
  if (_type == SocketTCPWin::CLIENT) {
    throw std::runtime_error("Try to connect with a server");
  }
  _addr.get().sin_family = AF_INET;
  _addr.get().sin_addr.s_addr = INADDR_ANY;
  _addr.get().sin_port = htons(port);
  if (::bind(_socket, (struct sockaddr *)&_addr.get(), sizeof(_addr.get())) == SOCKET_ERROR)
    DEBUG_MSG("Bind failed");
  else
    DEBUG_MSG("Bind done");
  return (0);
}

int	SocketTCPWin::listen(const int max)
{
  if (_type == SocketTCPWin::CLIENT) {
    throw std::runtime_error("Try to connect with a server");
  }
  ::listen(_socket, max);
  return (0);
}

ssize_t	SocketTCPWin::write(const Buffer &buf)
{
  if ((send(_socket, (const char *)buf.get(), buf.size(), 0)) == SOCKET_ERROR) {
    DEBUG_MSG("Send failed: " << WSAGetLastError());
  }
  return (0);
}

ssize_t	SocketTCPWin::write(const Buffer &buf, const Addr &addr)
{
  if ((send(addr.getSocket(), (const char *)buf.get(), buf.size(), 0)) == SOCKET_ERROR) {
    DEBUG_MSG("Send failed: " << WSAGetLastError());
  }
  return (0);
}

ssize_t	SocketTCPWin::write(const Paquet &paquet)
{
  if ((send(_socket, (const char *)paquet.getData(), paquet.getSize(), 0)) == SOCKET_ERROR) {
    DEBUG_MSG("Send failed: " << WSAGetLastError());
  }
  return (0);
}

ssize_t	SocketTCPWin::write(const Paquet &paquet, const Addr &addr)
{
  if ((send(addr.getSocket(), (const char *)paquet.getData(), paquet.getSize(), 0)) == SOCKET_ERROR) {
    DEBUG_MSG("Send failed: " << WSAGetLastError());
  }
  return (0);
}

ssize_t	SocketTCPWin::read(Buffer &buf)
{
  int		recvlen = 0;

  buf.reset();
  if ((recvlen = recv(_socket, (char *)buf.get(), buf.size(), 0)) == SOCKET_ERROR)
    DEBUG_MSG("Recv failed: " << WSAGetLastError());
  else {
//    DEBUG_MSG((char *)buf);
    buf.setSize(recvlen);
  }
  return (recvlen);
}

const Addr	SocketTCPWin::getAddr() const
{
  return (_addr);
}
