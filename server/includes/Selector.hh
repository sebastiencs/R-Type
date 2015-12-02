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
# include "Addr.hh"

class		Manager;

typedef std::map<uint8_t, std::function<void (const Buffer &, const Addr &)>>	listFunc;

class		Selector
{
private:
  std::weak_ptr<Manager>	_manager;

  listFunc	_selectorFunc;

  template<class Arg>
  auto resolver(void (Manager::*func)(Arg, const Addr &)) -> decltype(func)
    { return func; }

public:

  Selector(std::shared_ptr<Manager> manager);

  virtual ~Selector();

  int		execFunc(const Buffer &, const Addr &);
};

#endif /* !SELECTOR_H_ */
