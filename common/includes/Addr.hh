//
// Addr.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Mon Nov 16 03:43:12 2015 chapui_s
// Last update Mon Nov 16 03:43:12 2015 chapui_s
//

#ifndef ADDR_H_
# define ADDR_H_

# ifdef __unix__

#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <arpa/inet.h>
typedef int	socket_t;

# elif defined(_WIN32)

#  include "SocketsWin.hh"
typedef SOCKET	socket_t;

# endif

# include <algorithm>
# include <functional>

class				Addr
{
public:

  typedef enum { UDP, TCP, NONE } TypeAddr;

private:

  struct sockaddr_in		_addr;
  struct sockaddr_in		_addrUDP;
  socket_t			_socket;
  TypeAddr			_type;
  uint16_t			_port;

public:
  Addr();
  Addr(const Addr &);
  Addr(const struct sockaddr_in &);
  Addr(const socket_t &);
  Addr(const socket_t &, const struct sockaddr_in &, uint16_t port);
  virtual ~Addr();

  Addr				&operator=(const Addr &);

  void				set(struct sockaddr_in &);
  void				setPortUDP(uint16_t port);
  void				set(const socket_t &);
  const struct sockaddr_in	&get() const;
  struct sockaddr_in		&get();
  const struct sockaddr_in	&getUDP() const;
  struct sockaddr_in		&getUDP();
  const socket_t		&getSocket() const;
  uint16_t			getPort() const;

  bool				operator==(const Addr &) const;

  Addr::TypeAddr		getType() const;
};

std::ostream &operator<<(std::ostream &os, const Addr &o);

#endif /* !ADDR_H_ */
