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

# include <vector>
# include <functional>
# include <type_traits>
# include "Paquets.hh"
# include "Addr.hh"

class		Manager;

typedef std::shared_ptr<Manager>	Manager_SharedPtr;
typedef std::weak_ptr<Manager>		Manager_WeakPtr;

typedef std::vector<std::function<void (const Buffer &, const Addr &)>> listFunc;

class			Selector
{
private:
  Manager_WeakPtr	_manager;
  Manager		*_mPtr;

  listFunc		_func;

  template<class PaquetType>
  auto resolver(void (Manager::*func)(std::shared_ptr<PaquetType>, const Addr &)) -> decltype(func);

  template <typename PaquetType>
  void	call(const Buffer &buf, const Addr &addr);

public:

  Selector(const Manager_SharedPtr &&manager);
  virtual ~Selector();

  int		execFunc(const Buffer &, const Addr &);
};

#endif /* !SELECTOR_H_ */
