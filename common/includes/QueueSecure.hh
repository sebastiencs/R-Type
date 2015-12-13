//
// QueueSecure.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Dec 10 21:36:36 2015 chapui_s
// Last update Thu Dec 10 21:36:36 2015 chapui_s
//

#ifndef QUEUESECURE_H_
# define QUEUESECURE_H_

# include <queue>
# include <algorithm>
# include "Mutex.hh"

template<typename T>
class				QueueSecure
{
private:
  mutable Mutex	_mutex;
  std::queue<T>	_queue;

public:

  QueueSecure<T>	&operator=(QueueSecure<T> &&) = delete;

  template<typename... Args>
  void	push(Args&&... args) {
    _mutex.lock();
    _queue.push(args...);
    _mutex.unlock();
  };

  template<typename... Args>
  void	pop(Args&&... args) {
    _mutex.lock();
    _queue.pop(args...);
    _mutex.unlock();
  };

  template<typename... Args>
  void	emplace(Args&&... args) {
    _mutex.lock();
    _queue.emplace(std::move(args...));
    _mutex.unlock();
  };

  auto	front() const -> decltype(_queue.front()) {
    _mutex.lock();
    auto &&val = _queue.front();
    _mutex.unlock();
    return (val);
  };

  auto	empty() const -> decltype(_queue.empty()) {
    _mutex.lock();
    auto &&val = _queue.empty();
    _mutex.unlock();
    return (val);
  };

  auto	size() const -> decltype(_queue.size()) {
    _mutex.lock();
    auto &&val = _queue.size();
    _mutex.unlock();
    return (val);
  };

};

#endif /* !QUEUESECURE_H_ */
