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

#  include <netinet/in.h>
typedef int	socket_t;

# elif defined(_WIN32)

#  include <Windows.h>
typedef SOCKET	socket_t;

# endif

# include <algorithm>

class				Addr
{
private:

  typedef enum { UDP, TCP, NONE } TypeAddr;

  struct sockaddr_in		_addr;
  socket_t			_socket;
  TypeAddr			_type;

public:
  Addr();
  Addr(const struct sockaddr_in &);
  Addr(const socket_t &);
  virtual ~Addr();

  void				set(struct sockaddr_in &);
  void				set(const socket_t &);
  const struct sockaddr_in	&get() const;
  const socket_t		&getSocket() const;

  bool				operator==(const Addr &);
};

#endif /* !ADDR_H_ */
