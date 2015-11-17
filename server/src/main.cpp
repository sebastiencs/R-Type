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

#ifdef _WIN32
# include "WSA.hh"
#endif // !_WIN32

#ifndef DEFAULT_PORT
# define DEFAULT_PORT	(4242)
#endif // !DEFAULT_PORT

#include "Socket.hh"
#include "Paquets.hh"
#include "Timer.hh"

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

  server.reset(new Server(port));
  server->run();

  ISocketUDP *socket = new SocketUDP(SocketUDP::SERVER);

  char buffer[512];

  socket->bind(port);

  PaquetFirst paquet;
  paquet.setVersion(1);
  paquet.setName("sebastien");
  paquet.setLevel(10);
  paquet.createPaquet();
  std::cout << paquet << std::endl;

  PaquetRequestParties p2;
  p2.createPaquet();
  std::cout << p2 << std::endl;

  PaquetListParties p3;
  p3.addParty("sebastien", 10);
  p3.addParty("chapuis", 100);
  p3.createPaquet();
  std::cout << p3 << std::endl;

  PaquetJoinParty p4;
  p4.setName("Zizou");
  p4.createPaquet();
  std::cout << p4 << std::endl;

  PaquetCreateParty p5;
  p5.setName("Okok");
  p5.createPaquet();
  std::cout << p5 << std::endl;

  PaquetRequestPlayers p6;
  p6.createPaquet();
  std::cout << p6 << std::endl;

  PaquetListPlayers p7;
  p7.addPlayer("sebastien", 1, 10);
  p7.addPlayer("chapuis", 2, 100);
  p7.createPaquet();
  std::cout << p7 << std::endl;

  while (1) {

    Buffer buf;

    socket->read(buf);
    std::cout << "BUFFER: " << buf.get();

    socket << paquet;
    socket << p2;
    socket << p3;
    socket << p4;
    socket << p5;
    socket << p6;
    socket << p7;

//    socket->write(buffer, 10);
  }

  std::cout << "PORT: " << port << std::endl;

#ifdef _WIN32
  WSA::clean();
#endif // !_WIN32

  return (0);
}
