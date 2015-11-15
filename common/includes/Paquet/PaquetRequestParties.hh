//
// PaquetRequestParties.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sat Nov 14 04:53:01 2015 chapui_s
// Last update Sat Nov 14 04:53:01 2015 chapui_s
//

#ifndef PAQUETREQUESTPARTIES_H_
# define PAQUETREQUESTPARTIES_H_

# include "Paquet.hh"

class		PaquetRequestParties : public Paquet
{
private:
  uint8_t	_id;

public:
  PaquetRequestParties();
  PaquetRequestParties(void *, size_t);
  virtual ~PaquetRequestParties();

  void		createPaquet();
  void		parsePaquet();
};

std::ostream	&operator<<(std::ostream &, PaquetRequestParties &);

#endif /* !PAQUETREQUESTPARTIES_H_ */
