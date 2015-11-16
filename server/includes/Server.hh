//
// Server.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 10 22:39:54 2015 chapui_s
// Last update Tue Nov 10 22:39:54 2015 chapui_s
//

#ifndef SERVER_H_
# define SERVER_H_

# include <memory>
# include "Network.hh"
# include "Debug.hh"

class				Server
{
private:
  std::unique_ptr<Network>	_network;

public:
  Server(const uint16_t);
  virtual ~Server();

  int	run();
  int	stop();
};

#endif /* !SERVER_H_ */
