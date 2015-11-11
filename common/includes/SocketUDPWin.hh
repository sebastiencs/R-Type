//
// SocketUDPWin.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 15:37:18 2015 chapui_s
// Last update Wed Nov 11 15:37:18 2015 chapui_s
//

#ifndef SOCKETUDPWIN_H_
# define SOCKETUDPWIN_H_

# include "Debug.hh"
# include "ISocketUDP.hh"

class		SocketUDPWin : public ISocketUDP
{
public:

  typedef enum { SERVER = 2, CLIENT = 4 } CONNECTION_TYPE;

private:

public:

  SocketUDPWin(CONNECTION_TYPE);
  SocketUDPWin(CONNECTION_TYPE, socket_t);
  virtual ~SocketUDPWin();

  virtual int		connect(const std::string &, uint16_t);
  virtual int		bind(uint16_t);
  virtual ssize_t	write(const void *, size_t);
  virtual ssize_t	read(void *, size_t);
};


#endif /* !SOCKETUDPWIN_H_ */
