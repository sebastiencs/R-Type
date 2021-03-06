//
// SocketUDPWin.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 15:37:18 2015 chapui_s
// Last update Wed Nov 11 15:37:18 2015 chapui_s
//

#ifndef SOCKETUDPWIN_H_
# define SOCKETUDPWIN_H_

# include "Debug.hh"
# include "ISocketUDP.hh"
# include "Buffer.hh"

class		SocketUDPWin : public ISocketUDP
{
public:

  typedef enum { SERVER = 2, CLIENT = 4 } CONNECTION_TYPE;

private:
  bool	_isKnown;
  socket_t		_socket;
  sockaddr_in 		_addr;
  CONNECTION_TYPE	_type;

  int _clientLen;

public:

  SocketUDPWin(const CONNECTION_TYPE);
  SocketUDPWin(const CONNECTION_TYPE, const socket_t);
  virtual ~SocketUDPWin();

  virtual socket_t	socket() const;
  virtual int		connect(const std::string &, const uint16_t);
  virtual int		bind(const uint16_t);
  virtual ssize_t	write(const Buffer &buf);
  virtual ssize_t	write(const Buffer &buf, const Addr &);
  virtual ssize_t	write(const Paquet &paquet);
  virtual ssize_t	write(const Paquet &paquet, const Addr &);
  virtual ssize_t	read(Buffer &buf);
  virtual const Addr	getAddr() const;
};

#endif /* !SOCKETUDPWIN_H_ */
