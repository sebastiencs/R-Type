//
// SignalWin.hh for epitech in /home/bresci_b/R-Type
//
// Made by bresci_b
// Login   <bresci_b@epitech.eu>
//
// Started on  Sun Nov 29 18:46:32 2015 bresci_b
// Last update Sun Nov 29 18:46:32 2015 bresci_b
//

#ifndef SIGNALWIN_H_
# define SIGNALWIN_H_


# include <windows.h>
# include <map>
# include "Debug.hh"
# include "ISignal.hh"

typedef std::map<int, Handler_t>	listHandler;

class		SignalWin : public ISignal
{
private:
	listHandler	_listHandler;

public:
	SignalWin();
	virtual ~SignalWin();

	virtual void	addSignal(int, Handler_t);
	virtual bool	callHandler(int sig);
};

bool		sig_handler(int);
SignalWin	*class_save(SignalWin *ptr_class);


#endif /* !SIGNALWIN_H_ */
