//
// Selector.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Mon Nov 16 14:50:07 2015 chapui_s
// Last update Mon Nov 16 14:50:07 2015 chapui_s
//

#ifndef SELECTOR_H_
# define SELECTOR_H_

# include <map>
# include <functional>
# include "Paquets.hh"

class		Network;

class		Selector
{
private:
  Network	*_net;
  char		*_data;

  int		(Network::*_handleFirst)(PaquetFirst);

  std::map<uint8_t, std::function<int (ssize_t)>>	_selectorFunc;

public:
  Selector(Network *net) {
    _net = net;

    _handleFirst = &Network::handleFirst;

    _selectorFunc[Paquet::FIRST] = [this](ssize_t size) -> int { return ((_net->*_handleFirst)(PaquetFirst(_data, size))); };
    }

  virtual ~Selector() {};

  int		execFunc(char *, ssize_t);
};

int		Selector::execFunc(char *data, ssize_t size)
{
  _data = data;

  if (!data || size <= 0) {
    std::cerr << "Wrong paquet size" << std::endl;
    return (-1);
  }

  auto func = _selectorFunc.find(data[0]);

  if (func != _selectorFunc.end()) {
    return (func->second(size));
  }
  else {
    std::cerr << "Unknown paquet" << std::endl;
  }
  return (-1);
}

#endif /* !SELECTOR_H_ */
