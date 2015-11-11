//
// SocketTCPWin.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 15:33:41 2015 chapui_s
// Last update Wed Nov 11 15:33:41 2015 chapui_s
//

#ifndef SOCKETTCPWIN_H_
# define SOCKETTCPWIN_H_

# include "Debug.hh"
# include "ISocketTCP.hh"

class		SocketTCPWin : public ISocketTCP
{
public:

  typedef enum { SERVER = 2, CLIENT = 4 } CONNECTION_TYPE;

public:

  SocketTCPWin(CONNECTION_TYPE);
  SocketTCPWin(CONNECTION_TYPE, socket_t);
  virtual ~SocketTCPWin();

  virtual ISocketTCP	*accept();
  virtual int		connect(const std::string &, uint16_t);
  virtual int		bind(uint16_t);
  virtual int		listen(int);
  virtual ssize_t	write(const void *, size_t);
  virtual ssize_t	read(void *, size_t);
};

#endif /* !SOCKETTCPWIN_H_ */
