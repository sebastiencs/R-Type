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

# elif defined(_WIN32)

#  include <Windows.h>

# endif

# include <algorithm>

class				Addr
{
private:
  struct sockaddr_in		_addr;

public:
  Addr();
  Addr(const struct sockaddr_in &);
  virtual ~Addr();

  void				set(struct sockaddr_in &);
  const struct sockaddr_in	&get() const;

  bool				operator==(const Addr &);
};

#endif /* !ADDR_H_ */
