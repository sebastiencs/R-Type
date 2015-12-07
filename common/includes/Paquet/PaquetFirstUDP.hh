//
// PaquetFirst.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Fri Nov 13 21:34:17 2015 chapui_s
// Last update Fri Nov 13 21:34:17 2015 chapui_s
//

#ifndef PAQUETFIRSTUDP_H_
# define PAQUETFIRSTUDP_H_

# include "Paquet.hh"

class		PaquetFirstUDP : public Paquet
{
private:
  uint8_t	_id;
	uint8_t _playerId;

public:
	PaquetFirstUDP();
	PaquetFirstUDP(const Buffer &);
  template <typename T>
	PaquetFirstUDP(const T *data, size_t len) : Paquet(data, len) { parsePaquet(); }
  virtual ~PaquetFirstUDP();

  void		setId(uint8_t);

  uint8_t		getId() const;

  void		createPaquet();
  void		parsePaquet();
};

std::ostream	&operator<<(std::ostream &, PaquetFirstUDP &);

#endif /* !PAQUETFIRSTUDP_H_ */
