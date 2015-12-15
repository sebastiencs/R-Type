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
# include <memory>
# include "Mutex.hh"
# include "Locker.hh"

typedef std::shared_ptr<IMutex>	IMutex_SharedPtr;

template<typename T>
class				QueueSecure
{
private:
  mutable IMutex_SharedPtr	_mutex;
  std::queue<T>	_queue;

public:

  QueueSecure() : _mutex(std::make_shared<Mutex>()) {};
  virtual ~QueueSecure() {};

  QueueSecure<T>	&operator=(QueueSecure<T> &&) = delete;

  template<typename... Args>
  void	push(Args&&... args) {
    Locker<IMutex_SharedPtr> { _mutex };
    _queue.push(args...);
  };

  template<typename... Args>
  void	pop(Args&&... args) {
    Locker<IMutex_SharedPtr> { _mutex };
    _queue.pop(args...);
  };

  template<typename... Args>
  void	emplace(Args&&... args) {
    Locker<IMutex_SharedPtr> { _mutex };
    _queue.emplace(std::move(args...));
  };

  auto	front() const -> decltype(_queue.front()) {
    Locker<IMutex_SharedPtr> { _mutex };
    auto &&val = _queue.front();
    return (val);
  };

  auto	empty() const -> decltype(_queue.empty()) {
    Locker<IMutex_SharedPtr> { _mutex };
    auto &&val = _queue.empty();
    return (val);
  };

  auto	size() const -> decltype(_queue.size()) {
    Locker<IMutex_SharedPtr> { _mutex };
    auto &&val = _queue.size();
    return (val);
  };

};

#endif /* !QUEUESECURE_H_ */
