//
// IOEvent.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 24 17:45:19 2015 chapui_s
// Last update Tue Nov 24 17:45:19 2015 chapui_s
//

# include "IOEvent.hh"

IOEvent::IOEvent()
{
}

IOEvent::~IOEvent()
{
}

int	IOEvent::poll(Pollfd &fds, const int timeout)
{
#ifdef __unix__
  return (::poll(fds.data(), fds.size(), timeout));
#elif defined(_WIN32)
  return (WSAPoll(fds.data(), fds.size(), timeout));
#endif
}

int	IOEvent::wait(const int timeout)
{
#ifdef __unix__
  return (::poll(nullptr, 0, timeout));
#elif defined(_WIN32)
  Sleep(timeout);
  return (0);
#endif
}
