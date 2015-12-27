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

# include <iostream>
# include "Debug.hh"
# include "IDynamicLib.hh"
# include "SocketsWin.hh"

class		DynamicLibWin : public IDynamicLib
{
private:
	HINSTANCE 				_lib;
	std::function<void()>	_unused;

public:
	DynamicLibWin(const std::string &);
	virtual ~DynamicLibWin();

	virtual const Enemy_SharedPtr	getEnemy(const std::string &) const;
};

#endif /* !DYNAMICLIBWIN_H_ */
