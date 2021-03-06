//
// Tools.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 29 12:15:44 2015 chapui_s
// Last update Sun Nov 29 12:15:45 2015 chapui_s
//

#ifndef TOOLS_H_
# define TOOLS_H_

# include <algorithm>
# include <functional>
# include <cstdlib>
# include <ctime>
# include <memory>

#ifdef __unix__
#  include <unistd.h>
#elif defined(_WIN32)
# include <windows.h>
# include <Lmcons.h>
#endif


class Addr;
class Party;

namespace		Tools
{
  template<class T, class U>
  auto		findIn(const T &input, const U &func) -> typename T::value_type
  {
    auto found = std::find_if(input.begin(), input.end(), func);

    return ((found != input.end()) ? (*found) : (nullptr));
  };

  template<class T, class U>
  auto		findIt(const T &input, const U &func) -> decltype(input.begin())
  {
    auto found = std::find_if(input.begin(), input.end(), func);

    return (found);
  };

  template<class U>
  auto		findIn(const std::string &input, const U &func) -> bool
  {
    auto found = std::find_if(input.begin(), input.end(), func);

    return ((found != input.end()) ? (true) : (false));
  }

  int			random(const int min, int max);
  const std::string	&getUser();

};

#endif /* !TOOLS_H_ */
