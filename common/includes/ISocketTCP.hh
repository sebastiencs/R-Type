//
// ISocketTCP.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 03:33:02 2015 chapui_s
// Last update Wed Nov 11 03:33:02 2015 chapui_s
//

#ifndef ISOCKETTCP_H_
# define ISOCKETTCP_H_

# ifdef __unix__

#  include <sys/types.h>
#  include <sys/socket.h>
typedef int	socket_t;

# elif defined(_WIN32)

#  include "SocketsWin.hh"
typedef SOCKET	socket_t;
typedef SSIZE_T ssize_t;

# else

#  error "Platform unknown"

# endif

# include <memory>
# include <string>
# include "Buffer.hh"
# include "Addr.hh"
# include "Paquet.hh"

class		ISocketTCP
{
public:

  virtual ~ISocketTCP() {};

  virtual socket_t	socket() const = 0;
  virtual ISocketTCP	*accept() = 0;
  virtual int		connect(const std::string &, const uint16_t) = 0;
  virtual int		bind(const uint16_t) = 0;
  virtual int		listen(const int) = 0;
  virtual ssize_t	write(const Buffer &buf) = 0;
  virtual ssize_t	write(const Buffer &buf, const Addr &addr) = 0;
  virtual ssize_t	write(const Paquet &paquet) = 0;
  virtual ssize_t	write(const Paquet &paquet, const Addr &addr) = 0;
  virtual ssize_t	read(Buffer &) = 0;
  virtual const Addr	getAddr() const = 0;
};

typedef std::shared_ptr<ISocketTCP>	ISocketTCP_SharedPtr;
typedef std::unique_ptr<ISocketTCP>	ISocketTCP_UniquePtr;
typedef std::weak_ptr<ISocketTCP>	ISocketTCP_WeakPtr;

#endif /* !ISOCKETTCP_H_ */
