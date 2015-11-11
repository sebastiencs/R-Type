//
// Network.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 10 22:59:35 2015 chapui_s
// Last update Tue Nov 10 22:59:35 2015 chapui_s
//

#ifndef NETWORK_H_
# define NETWORK_H_

# include <iostream>
# include "Debug.hh"

class				Network
{
private:
  const uint16_t		_port;

public:
  Network(const uint16_t);
  virtual ~Network();
};

#endif /* !NETWORK_H_ */
