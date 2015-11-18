//
// ISocketUDP.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 10:30:12 2015 chapui_s
// Last update Wed Nov 11 10:30:12 2015 chapui_s
//

#ifndef ISOCKETUDP_H_
# define ISOCKETUDP_H_

# ifdef __unix__

#  include <sys/types.h>
#  include <sys/socket.h>
typedef int	socket_t;

# elif defined(_WIN32)

#  include <BaseTsd.h>
#  include <winsock2.h>
#  include <Ws2tcpip.h>
#  pragma comment(lib, "ws2_32.lib")
typedef SOCKET	socket_t;
typedef SSIZE_T ssize_t;
typedef struct sockaddr_in sockaddr_in;

# else

#  error "Platform unknown"

# endif

# include <string>
# include "Addr.hh"
# include "Buffer.hh"
# include "Paquet.hh"

class		ISocketUDP
{
public:

  virtual ~ISocketUDP() {};

  virtual int		connect(const std::string &, uint16_t port) = 0;
  virtual int		bind(uint16_t port) = 0;
  virtual ssize_t	write(const Buffer &buf) = 0;
  virtual ssize_t	write(const Buffer &buf, const Addr &addr) = 0;
  virtual ssize_t	write(const Paquet &paquet) = 0;
  virtual ssize_t	write(const Paquet &paquet, const Addr &addr) = 0;
  virtual ssize_t	read(Buffer &buf) = 0;
  virtual const Addr	getAddr() const = 0;
};

#endif /* !ISOCKETUDP_H_ */
