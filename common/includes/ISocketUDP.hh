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
#  pragma comment(lib, "ws2_32.lib")
typedef SOCKET	socket_t;
typedef SSIZE_T ssize_t;
typedef struct sockaddr_in sockaddr_in;

# else

#  error "Platform unknown"

# endif

# include <string>
# include "Addr.hh"

class		ISocketUDP
{
public:

  virtual ~ISocketUDP() {};

  virtual int		connect(const std::string &, uint16_t) = 0;
  virtual int		bind(uint16_t) = 0;
  virtual ssize_t	write(const void *, size_t) = 0;
  virtual ssize_t	write(const void *, size_t, const Addr &) = 0;
  virtual ssize_t	read(void *, size_t) = 0;
};

#endif /* !ISOCKETUDP_H_ */
