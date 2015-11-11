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

class		SocketTCPUnix : public ISocketTCP
{
public:

  typedef enum { SERVER = 2, CLIENT = 4 } CONNECTION_TYPE;

private:
  socket_t		_fd;
  int			_error;
  struct sockaddr_in	_addr;
  CONNECTION_TYPE	_type;

public:

  SocketTCPUnix(CONNECTION_TYPE);
  SocketTCPUnix(CONNECTION_TYPE, socket_t);
  virtual ~SocketTCPUnix();

  virtual ISocketTCP	*accept();
  virtual int		connect(const std::string &, uint16_t);
  virtual int		bind(uint16_t);
  virtual int		listen(int);
  virtual ssize_t	write(const void *, size_t);
  virtual ssize_t	read(void *, size_t);
};

#endif /* !SOCKETTCPUNIX_H_ */
