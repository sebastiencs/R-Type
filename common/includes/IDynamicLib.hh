//
// IDynamicLib.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 11:42:30 2015 chapui_s
// Last update Wed Nov 11 11:42:30 2015 chapui_s
//

#ifndef IDYNAMICLIB_H_
# define IDYNAMICLIB_H_

# include <functional>

class		IDynamicLib
{
public:
  virtual ~IDynamicLib() {};

  virtual std::function<void()>	getFunc(const std::string &) const = 0;
};


#endif /* !IDYNAMICLIB_H_ */
