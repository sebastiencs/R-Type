//
// PaquetListPlayers.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sat Nov 14 05:00:44 2015 chapui_s
// Last update Sat Nov 14 05:00:44 2015 chapui_s
//

#ifndef PAQUETLISTPLAYERS_H_
# define PAQUETLISTPLAYERS_H_

# include <list>
# include <tuple>
# include "Paquet.hh"

class		PaquetListPlayers : public Paquet
{
private:
  uint8_t						_id;
  uint16_t						_nbPlayers;
  std::list<std::tuple<std::string, uint8_t, uint8_t>>	_listPlayers;

public:
  PaquetListPlayers();
  PaquetListPlayers(void *, size_t);
  virtual ~PaquetListPlayers();

  void		addPlayer(const std::string &, uint8_t, uint8_t);

  const std::list<std::tuple<std::string, uint8_t, uint8_t>>	&getPlayers() const;

  void		createPaquet();
  void		parsePaquet();
};

std::ostream	&operator<<(std::ostream &, PaquetListPlayers &);

#endif /* !PAQUETLISTPLAYERS_H_ */