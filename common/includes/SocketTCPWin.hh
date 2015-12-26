//
// SocketTCPWin.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 15:33:41 2015 chapui_s
// Last update Wed Nov 11 15:33:41 2015 chapui_s
//

#ifndef SOCKETTCPWIN_H_
# define SOCKETTCPWIN_H_

# include "Debug.hh"
# include "Buffer.hh"
# include "ISocketTCP.hh"

class		SocketTCPWin : public ISocketTCP
{
public:

  typedef enum { SERVER = 2, CLIENT = 4 } CONNECTION_TYPE;

protected:

  socket_t	_socket;
  Addr		_addr;
  uint16_t	_port;
  // sockaddr_in _server;
  // sockaddr_in _client;

  CONNECTION_TYPE	_type;

  int _clientLen;
public:

  SocketTCPWin(const CONNECTION_TYPE);
  SocketTCPWin(const CONNECTION_TYPE, const socket_t, struct sockaddr_in &, const uint16_t);
  virtual ~SocketTCPWin();

  virtual socket_t	socket() const;
  virtual ISocketTCP	*accept();
  virtual int	  connect(const std::string &, const uint16_t);
  virtual int		bind(const uint16_t);
  virtual int		listen(const int);
  virtual ssize_t	write(const Buffer &buf);
  virtual ssize_t	write(const Buffer &buf, const Addr &addr);
  virtual ssize_t	write(const Paquet &paquet);
  virtual ssize_t	write(const Paquet &paquet, const Addr &addr);
  virtual ssize_t	read(Buffer &buf);
  virtual const Addr	getAddr() const;
};


#endif /* !SOCKETTCPWIN_H_ */
