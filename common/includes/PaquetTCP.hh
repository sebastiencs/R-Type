//
// PaquetTCP.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Dec  2 01:06:35 2015 chapui_s
// Last update Wed Dec  2 01:06:35 2015 chapui_s
//

#ifndef PAQUETTCP_H_
# define PAQUETTCP_H_

# include <map>
# include "Socket.hh"

class		PaquetTCP : public SocketTCP
{
private:
  std::unique_ptr<Buffer>	_buffer;
  std::unique_ptr<Buffer>	_bufferTMP;
  bool				_start;
  uint16_t			_sizeCurrent;
  uint16_t			_sizePaquet;
  uint8_t			_idPaquet;

  std::map<uint8_t, uint16_t>	_pSize;

  enum {
    UNKNOWN_SIZE = 0xFFFF
  };

  void		initSize();
  ssize_t	readDone(Buffer &);

public:
  PaquetTCP(SocketTCP::CONNECTION_TYPE);
  PaquetTCP(CONNECTION_TYPE type, socket_t fd, struct sockaddr_in &addr, uint16_t port);
  virtual ~PaquetTCP();

  virtual ISocketTCP	*accept();
  virtual ssize_t	read(Buffer &);
};

#endif /* !PAQUETTCP_H_ */
