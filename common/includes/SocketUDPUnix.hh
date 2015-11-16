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
  struct sockaddr_in	_clientAddr;
  CONNECTION_TYPE	_type;

  bool			_isKnown;

public:

  SocketUDPUnix(CONNECTION_TYPE);
  SocketUDPUnix(CONNECTION_TYPE, socket_t);
  virtual ~SocketUDPUnix();

  virtual int		connect(const std::string &, uint16_t);
  virtual int		bind(uint16_t);
  virtual ssize_t	write(const void *, size_t);
  virtual ssize_t	write(const void *, size_t, const Addr &);
  virtual ssize_t	read(void *, size_t);
  virtual const Addr	getAddr() const;
};


#endif /* !SOCKETUDPUNIX_H_ */
