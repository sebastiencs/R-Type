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
# include <memory>
# include "Mutex.hh"
# include "Locker.hh"

typedef std::shared_ptr<IMutex>	IMutex_SharedPtr;

template<typename T>
class				DequeSecure
{
private:
  mutable IMutex_SharedPtr	_mutex;
  std::deque<T>	_deque;

public:

  DequeSecure() : _mutex(std::make_shared<Mutex>()) {};
  virtual ~DequeSecure() {};

  DequeSecure<T>	&operator=(DequeSecure<T> &&) = delete;

  template<typename... Args>
  void	push_back(Args&&... args) {
    Locker<IMutex_SharedPtr> { _mutex };
    _deque.push_back(args...);
  };

  template<typename... Args>
  void	emplace_back(Args&&... args) {
    Locker<IMutex_SharedPtr> { _mutex };
    _deque.emplace_back(std::move(args...));
  };

  template<typename... Args>
  void	remove(Args&&... args) {
    Locker<IMutex_SharedPtr> { _mutex };
    _deque.remove(args...);
  };

  void	pop_front() {
    Locker<IMutex_SharedPtr> { _mutex };
    _deque.pop_front();
  };

  template<typename... Args>
  void	erase(Args&&... args) {
    Locker<IMutex_SharedPtr> { _mutex };
    _deque.erase(args...);
  };

  template<typename... Args>
  void	remove_if(Args&&... args) {
    Locker<IMutex_SharedPtr> { _mutex };
    _deque.remove_if(args...);
  };

  void	clear() {
    Locker<IMutex_SharedPtr> { _mutex };
    _deque.clear();
  };

  auto	front() const -> decltype(_deque.front()) {
    Locker<IMutex_SharedPtr> { _mutex };
    auto &&val = _deque.front();
    return (val);
  };

  auto	empty() const -> decltype(_deque.empty()) {
    Locker<IMutex_SharedPtr> { _mutex };
    auto val = _deque.empty();
    return (val);
  };

  auto	size() const -> decltype(_deque.size()) {
    Locker<IMutex_SharedPtr> { _mutex };
    auto val = _deque.size();
    return (val);
  };

  auto	begin() const -> decltype(_deque.begin()) {
    Locker<IMutex_SharedPtr> { _mutex };
    auto &&val = _deque.begin();
    return (val);
  };

  auto	end() const -> decltype(_deque.end()) {
    Locker<IMutex_SharedPtr> { _mutex };
    auto &&val = _deque.end();
    return (val);
  };

};

#endif /* !DEQUESECURE_H_ */
