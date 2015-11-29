//
// ISignal.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 29 18:44:29 2015 chapui_s
// Last update Sun Nov 29 18:44:29 2015 chapui_s
//

#ifndef ISIGNAL_H_
# define ISIGNAL_H_

# include <functional>

class		Server;

typedef std::function<void (void)>	Handler_t;

class		ISignal
{
public:
  virtual ~ISignal() {};

  virtual void	addSignal(int signal_id, Handler_t handler) = 0;
  virtual bool	callHandler(int) = 0;
};

#endif /* !ISIGNAL_H_ */
