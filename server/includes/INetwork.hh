//
// INetwork.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Fri Nov 13 19:26:25 2015 chapui_s
// Last update Fri Nov 13 19:26:25 2015 chapui_s
//

#ifndef INETWORK_H_
# define INETWORK_H_

# include "Paquets.hh"

# ifdef __unix__

#  include <poll.h>

# endif

class		INetwork
{
public:
  virtual ~INetwork() {};

  virtual int	run() = 0;
  virtual int	stop() = 0;
  virtual bool	write(const Paquet &, const Addr &) = 0;
};


#endif /* !INETWORK_H_ */
