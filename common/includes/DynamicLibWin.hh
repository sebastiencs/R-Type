//
// DynamicLibWin.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 15:31:16 2015 chapui_s
// Last update Wed Nov 11 15:31:16 2015 chapui_s
//

#ifndef DYNAMICLIBWIN_H_
# define DYNAMICLIBWIN_H_

# include "Debug.hh"
# include "IDynamicLib.hh"

class		DynamicLibWin : public IDynamicLib
{
private:
  void			*_lib;
  std::function<void()>	_unused;

public:
  DynamicLibWin(const std::string &);
  virtual ~DynamicLibWin();

  virtual std::function<void()>	getFunc(const std::string &) const;
};

#endif /* !DYNAMICLIBWIN_H_ */
