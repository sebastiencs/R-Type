//
// PaquetRequestPlayers.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sat Nov 14 04:53:01 2015 chapui_s
// Last update Sat Nov 14 04:53:01 2015 chapui_s
//

#ifndef PAQUETREQUESTPLAYERS_H_
# define PAQUETREQUESTPLAYERS_H_

# include "Paquet.hh"

class		PaquetRequestPlayers : public Paquet
{
private:
  uint8_t	_id;

public:
  PaquetRequestPlayers();
  PaquetRequestPlayers(const Buffer &);
  template <typename T>
  PaquetRequestPlayers(const T *data, size_t len) : Paquet(data, len) { parsePaquet(); }
  virtual ~PaquetRequestPlayers();

  void		createPaquet();
  void		parsePaquet();
};

std::ostream	&operator<<(std::ostream &, PaquetRequestPlayers &);

#endif /* !PAQUETREQUESTPLAYERS_H_ */
