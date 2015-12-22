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
# include <algorithm>
# include <memory>
# include "Mutex.hh"
# include "Locker.hh"

typedef std::shared_ptr<IMutex>	IMutex_SharedPtr;

template<typename T>
class				ListSecure
{
private:
  mutable IMutex_SharedPtr	_mutex;
  std::list<T>	_list;

public:

  using value_type = T;

  ListSecure() : _mutex(std::make_shared<Mutex>()) {};
  virtual ~ListSecure() {};

  ListSecure<T>	&operator=(ListSecure<T> &&) = delete;

  template<typename... Args>
  void	push_back(Args&&... args) {
    Locker<IMutex_SharedPtr> unused(_mutex);
    _list.push_back(args...);
  };

  template<typename... Args>
  void	emplace_back(Args&&... args) {
    Locker<IMutex_SharedPtr> unused(_mutex);
    _list.emplace_back(std::move(args...));
  };

  template<typename... Args>
  void	remove(Args&&... args) {
    Locker<IMutex_SharedPtr> unused(_mutex);
    _list.remove(args...);
  };

  template<typename... Args>
  void	remove_if(Args&&... args) {
    Locker<IMutex_SharedPtr> unused(_mutex);
    _list.remove_if(args...);
  };

  void	clear() {
    Locker<IMutex_SharedPtr> unused(_mutex);
    _list.clear();
  };

  void	pop_front() {
    Locker<IMutex_SharedPtr> unused(_mutex);
    _list.pop_front();
  };

  auto	front() const -> decltype(_list.front()) {
    Locker<IMutex_SharedPtr> unused(_mutex);
    auto &&val = _list.front();
    return (val);
  };

  auto	empty() const -> decltype(_list.empty()) {
    Locker<IMutex_SharedPtr> unused(_mutex);
    auto &&val = _list.empty();
    return (val);
  };

  auto	size() const -> decltype(_list.size()) {
    Locker<IMutex_SharedPtr> unused(_mutex);
    auto &&val = _list.size();
    return (val);
  };

  auto	begin() const -> decltype(_list.begin()) {
    Locker<IMutex_SharedPtr> unused(_mutex);
    auto &&val = _list.begin();
    return (val);
  };

  auto	end() const -> decltype(_list.end()) {
    Locker<IMutex_SharedPtr> unused(_mutex);
    auto &&val = _list.end();
    return (val);
  };

  template <class U>
  size_t count_if(const U &func) const {

    Locker<IMutex_SharedPtr> unused(_mutex);
    auto n = std::count_if(_list.begin(), _list.end(), func);

    return (n);
  };

  template <class U>
  auto findIn(const U &func) const -> T {

    Locker<IMutex_SharedPtr> unused(_mutex);
    auto &&found = std::find_if(_list.begin(), _list.end(), func);
    auto ptr = (found == _list.end()) ? (nullptr) : (*found);

    return (ptr);
  };

  template <class U>
  auto find_if_nolock(const U &func) const -> T {

    auto &&found = std::find_if(_list.begin(), _list.end(), func);
    auto ptr = (found == _list.end()) ? (nullptr) : (*found);

    return (ptr);
  };

  template <class U>
  void for_each(const U &func) const {

    Locker<IMutex_SharedPtr> unused(_mutex);
    std::for_each(_list.begin(), _list.end(), func);

  };

  template <class U>
  void for_each_nolock(const U &func) const {

    std::for_each(_list.begin(), _list.end(), func);

  };

};

#endif /* !LISTSECURE_H_ */
