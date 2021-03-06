//
// main.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 10 21:46:27 2015 chapui_s
// Last update Tue Nov 10 21:46:27 2015 chapui_s
//

#include "Server.hh"

#ifdef _WIN32
# include "WSA.hh"
#endif // !_WIN32

#ifndef DEFAULT_PORT
# define DEFAULT_PORT	(4242)
#endif // !DEFAULT_PORT

int				main(int argc, char **argv)
{
  std::unique_ptr<Server>	server;
  uint16_t			port = DEFAULT_PORT;

  if (argc >= 2) {
    port = std::stoi(argv[1]);
  }

#ifdef _WIN32
  if (WSA::init()) {
    return (-1);
  }
#endif // !_WIN32

  server = std::make_unique<Server>(port);
  server->run();

#ifdef _WIN32
  WSA::clean();
#endif // !_WIN32

  return (0);
}
