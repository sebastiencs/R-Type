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
typedef struct pollfd	_pollfd;

# elif defined(_WIN32)

# include "SocketsWin.hh"
typedef WSAPOLLFD	_pollfd;

# endif

typedef std::vector<_pollfd>	Pollfd;

class		IOEvent
{
public:
  IOEvent();
  virtual ~IOEvent();

  enum {
    POLL_WAIT = -1
  };

  static int	poll(Pollfd &fds, int timeout);
  static int	wait(int timeout);
};

#endif /* !IOEVENT_H_ */
