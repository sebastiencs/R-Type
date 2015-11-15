//
// PaquetJoinParty.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sat Nov 14 23:59:44 2015 chapui_s
// Last update Sat Nov 14 23:59:44 2015 chapui_s
//

#ifndef PAQUETJOINPARTY_H_
# define PAQUETJOINPARTY_H_

# include "Paquet.hh"

class		PaquetJoinParty : public Paquet
{
private:
  uint8_t	_id;
  std::string	_name;

public:
  PaquetJoinParty();
  PaquetJoinParty(void *, size_t);
  virtual ~PaquetJoinParty();

  void			setName(const std::string &);
  const std::string	getName() const;

  void			createPaquet();
  void			parsePaquet();
};

std::ostream	&operator<<(std::ostream &, PaquetJoinParty &);

#endif /* !PAQUETJOINPARTY_H_ */
