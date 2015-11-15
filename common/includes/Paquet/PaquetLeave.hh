//
// PaquetLeave.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 15 23:01:26 2015 chapui_s
// Last update Sun Nov 15 23:01:26 2015 chapui_s
//

#ifndef PAQUETLEAVE_H_
# define PAQUETLEAVE_H_

# include "Paquet.hh"

class		PaquetLeave : public Paquet
{
private:
  uint8_t	_id;
  uint8_t	_playerID;

public:
  PaquetLeave();
  PaquetLeave(void *, size_t);
  virtual ~PaquetLeave();

  void		setID(uint8_t);

  uint8_t	getID() const;

  void		createPaquet();
  void		parsePaquet();
};

std::ostream	&operator<<(std::ostream &, PaquetLeave &);

#endif /* !PAQUETLEAVE_H_ */
