//
// main.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 10 21:46:27 2015 chapui_s
// Last update Tue Nov 10 21:46:27 2015 chapui_s
//

#include <iostream>
#include <string>

#define DEFAULT_PORT	(4242)

int		main(int argc, char **argv)
{
  uint16_t	port = DEFAULT_PORT;

  if (argc >= 2) {
    port = std::stoi(argv[1]);
  }

  std::cout << "PORT: " << port << std::endl;
  return (0);
}
