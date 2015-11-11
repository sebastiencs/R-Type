//
// main.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 10 21:46:27 2015 chapui_s
// Last update Tue Nov 10 21:46:27 2015 chapui_s
//

#include <memory>
#include <iostream>
#include <string>
#include "Server.hh"

#ifndef DEFAULT_PORT
# define DEFAULT_PORT	(4242)
#endif // !DEFAULT_PORT

#include "Socket.hh"

int				main(int argc, char **argv)
{
  std::unique_ptr<Server>	server;
  uint16_t			port = DEFAULT_PORT;

  if (argc >= 2) {
    port = std::stoi(argv[1]);
  }

  server.reset(new Server(port));

  ISocketTCP *socket = new SocketTCP(SocketTCPUnix::SERVER);

  char buffer[512];

  socket->bind(port);
  socket->listen(10);

  ISocketTCP *client = socket->accept();

  while (1) {
    if (client->read(buffer, 10) > 0) {
      std::cout << "BUFFER: " << buffer;
    }
  }

  std::cout << "PORT: " << port << std::endl;


  return (0);
}
