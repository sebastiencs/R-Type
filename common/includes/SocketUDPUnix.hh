//
// SocketUDPUnix.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 10:22:14 2015 chapui_s
// Last update Wed Nov 11 10:22:14 2015 chapui_s
//

#ifndef SOCKETUDPUNIX_H_
# define SOCKETUDPUNIX_H_

# include <unistd.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <string>
# include "Debug.hh"
# include "ISocketUDP.hh"

class		SocketUDPUnix : public ISocketUDP
{
public:

  typedef enum { SERVER = 2, CLIENT = 4 } CONNECTION_TYPE;

private:
  int			_fd;
  int			_error;
  struct sockaddr_in	_addr;
  CONNECTION_TYPE	_type;

  bool			_isKnown;

public:

  SocketUDPUnix(const CONNECTION_TYPE);
  virtual ~SocketUDPUnix();

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


#endif /* !SOCKETUDPUNIX_H_ */
