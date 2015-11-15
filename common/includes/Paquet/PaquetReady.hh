//
// PaquetReady.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 15 22:49:45 2015 chapui_s
// Last update Sun Nov 15 22:49:45 2015 chapui_s
//

#ifndef PAQUETREADY_H_

# define PAQUETREADY_H_
# include "Paquet.hh"

class		PaquetReady : public Paquet
{
private:
  uint8_t	_id;
  uint8_t	_playerID;

public:
  PaquetReady();
  PaquetReady(void *, size_t);
  virtual ~PaquetReady();

  void		setID(uint8_t);

  uint8_t	getID() const;

  void		createPaquet();
  void		parsePaquet();
};

std::ostream	&operator<<(std::ostream &, PaquetReady &);

#endif /* !PAQUETREADY_H_ */
