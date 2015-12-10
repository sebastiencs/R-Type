//
// ListSecure.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Dec 10 21:36:36 2015 chapui_s
// Last update Thu Dec 10 21:36:36 2015 chapui_s
//

#ifndef LISTSECURE_H_
# define LISTSECURE_H_

# include <list>
# include "Mutex.hh"

template<typename T>
class				ListSecure : public std::list<T>
{
private:
  mutable Mutex	_mutex;
  std::list<T>	_list;

public:

  ListSecure<T>	&operator=(ListSecure<T>) = delete;
  ListSecure<T>	&operator=(ListSecure<T> &) = delete;
  ListSecure<T>	&operator=(ListSecure<T> &&) = delete;

  template<typename... Args>
  void	push_back(Args&&... args) {
    _mutex.lock();
    _list.push_back(args...);
    _mutex.unlock();
  };

  template<typename... Args>
  void	emplace_back(Args&&... args) {
    _mutex.lock();
    _list.emplace_back(std::move(args...));
    _mutex.unlock();
  };

  template<typename... Args>
  void	remove(Args&&... args) {
    _mutex.lock();
    _list.remove(args...);
    _mutex.unlock();
  };

  template<typename... Args>
  void	remove_if(Args&&... args) {
    _mutex.lock();
    _list.remove_if(args...);
    _mutex.unlock();
  };

  void	clear() {
    _mutex.lock();
    _list.clear();
    _mutex.unlock();
  };

  auto	front() const -> decltype(_list.front()) {
    _mutex.lock();
    auto &&val = _list.front();
    _mutex.unlock();
    return (val);
  };

  auto	empty() const -> decltype(_list.empty()) {
    _mutex.lock();
    auto &&val = _list.empty();
    _mutex.unlock();
    return (val);
  };

  auto	size() const -> decltype(_list.size()) {
    _mutex.lock();
    auto &&val = _list.size();
    _mutex.unlock();
    return (val);
  };

  auto	begin() const -> decltype(_list.begin()) {
    _mutex.lock();
    auto &&val = _list.begin();
    _mutex.unlock();
    return (val);
  };

  auto	end() const -> decltype(_list.end()) {
    _mutex.lock();
    auto &&val = _list.end();
    _mutex.unlock();
    return (val);
  };

};

#endif /* !LISTSECURE_H_ */
