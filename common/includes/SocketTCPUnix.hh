//
// SocketTCPUnix.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 02:45:16 2015 chapui_s
// Last update Wed Nov 11 02:45:16 2015 chapui_s
//

#ifndef SOCKETTCPUNIX_H_
# define SOCKETTCPUNIX_H_

# include <unistd.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <string>
# include "Debug.hh"
# include "ISocketTCP.hh"
# include "Buffer.hh"

class		SocketTCPUnix : public ISocketTCP
{
public:

  typedef enum { SERVER = 2, CLIENT = 4 } CONNECTION_TYPE;

protected:
  socket_t		_socket;
  int			_error;
  Addr			_addr;
  CONNECTION_TYPE	_type;
  uint16_t		_port;

public:

  SocketTCPUnix(CONNECTION_TYPE);
  SocketTCPUnix(CONNECTION_TYPE, socket_t, struct sockaddr_in &, uint16_t);
  virtual ~SocketTCPUnix();

  virtual socket_t	socket() const;
  virtual ISocketTCP	*accept();
  virtual int		connect(const std::string &, uint16_t);
  virtual int		bind(uint16_t port);
  virtual int		listen(int max);
  virtual ssize_t	write(const Buffer &buf);
  virtual ssize_t	write(const Buffer &buf, const Addr &addr);
  virtual ssize_t	write(const Paquet &paquet);
  virtual ssize_t	write(const Paquet &paquet, const Addr &);
  virtual ssize_t	read(Buffer &);
  virtual const Addr	getAddr() const;
};

#endif /* !SOCKETTCPUNIX_H_ */
