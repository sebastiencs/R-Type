//
// DequeSecure.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Dec 10 21:36:36 2015 chapui_s
// Last update Thu Dec 10 21:36:36 2015 chapui_s
//

#ifndef DEQUESECURE_H_
# define DEQUESECURE_H_

# include <deque>
# include <algorithm>
# include "Mutex.hh"

template<typename T>
class				DequeSecure
{
private:
  mutable Mutex	_mutex;
  std::deque<T>	_deque;

public:

  DequeSecure<T>	&operator=(DequeSecure<T> &&) = delete;

  template<typename... Args>
  void	push_back(Args&&... args) {
    _mutex.lock();
    _deque.push_back(args...);
    _mutex.unlock();
  };

  template<typename... Args>
  void	emplace_back(Args&&... args) {
    _mutex.lock();
    _deque.emplace_back(std::move(args...));
    _mutex.unlock();
  };

  template<typename... Args>
  void	remove(Args&&... args) {
    _mutex.lock();
    _deque.remove(args...);
    _mutex.unlock();
  };

  template<typename... Args>
  void	erase(Args&&... args) {
    _mutex.lock();
    _deque.erase(args...);
    _mutex.unlock();
  };

  template<typename... Args>
  void	remove_if(Args&&... args) {
    _mutex.lock();
    _deque.remove_if(args...);
    _mutex.unlock();
  };

  void	clear() {
    _mutex.lock();
    _deque.clear();
    _mutex.unlock();
  };

  auto	front() const -> decltype(_deque.front()) {
    _mutex.lock();
    auto &&val = _deque.front();
    _mutex.unlock();
    return (val);
  };

  auto	empty() const -> decltype(_deque.empty()) {
    _mutex.lock();
    auto &&val = _deque.empty();
    _mutex.unlock();
    return (val);
  };

  auto	size() const -> decltype(_deque.size()) {
    _mutex.lock();
    auto &&val = _deque.size();
    _mutex.unlock();
    return (val);
  };

  auto	begin() const -> decltype(_deque.begin()) {
    _mutex.lock();
    auto &&val = _deque.begin();
    _mutex.unlock();
    return (val);
  };

  auto	end() const -> decltype(_deque.end()) {
    _mutex.lock();
    auto &&val = _deque.end();
    _mutex.unlock();
    return (val);
  };

};

#endif /* !DEQUESECURE_H_ */
