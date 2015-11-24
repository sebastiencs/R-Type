//
// IOEvent.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 24 17:42:12 2015 chapui_s
// Last update Tue Nov 24 17:42:12 2015 chapui_s
//

#ifndef IOEVENT_H_
# define IOEVENT_H_

# include <vector>

# ifdef __unix__

# include <poll.h>
typedef std::vector<struct pollfd>	Pollfd;

# elif defined(_WIN32)

# include "SocketsWin.hh"
typedef std::vector<WSAPOLLFD>		Pollfd;

# endif

class		IOEvent
{
public:
  IOEvent();
  virtual ~IOEvent();

  static int	poll(Pollfd &fds, int timeout);
};

#endif /* !IOEVENT_H_ */
