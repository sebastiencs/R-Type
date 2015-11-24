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

class		Manager;

typedef std::map<uint8_t, std::function<void (const Buffer &)>>	listFunc;

class		Selector
{
private:
  Manager	*_manager;

  listFunc	_selectorFunc;

public:

  template<class Arg, class Ret>
  auto resolver(Ret (Manager::*m)(Arg)) -> decltype(m)
    { return m; }

  Selector(Manager *manager) {
   _manager = manager;

   _selectorFunc[Paquet::FIRST] = [this](const Buffer &buf) { (_manager->*resolver<PaquetFirst *>(&Manager::handlePaquet))(new PaquetFirst(buf)) };
    }

  virtual ~Selector() {};

  int		execFunc(const Buffer &);
};

int		Selector::execFunc(const Buffer &buf)
{
  Data		*data = buf.get();

  if (!data || buf.size() <= 0) {
    std::cerr << "Wrong paquet size" << std::endl;
    return (-1);
  }

  auto func = _selectorFunc.find(data[0]);

  if (func != _selectorFunc.end()) {
    func->second(buf);
    return (0);
  }
  else {
    std::cerr << "Unknown paquet" << std::endl;
    return (-1);
  }
}

#endif /* !SELECTOR_H_ */
