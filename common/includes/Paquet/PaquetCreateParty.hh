//
// PaquetCreateParty.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 15 02:20:11 2015 chapui_s
// Last update Sun Nov 15 02:20:11 2015 chapui_s
//

#ifndef PAQUETCREATEPARTY_H_
# define PAQUETCREATEPARTY_H_

# include "Paquet.hh"

class		PaquetCreateParty : public Paquet
{
private:
  uint8_t	_id;
  std::string	_name;

public:
  PaquetCreateParty();
  PaquetCreateParty(const Buffer &);
  template <typename T>
  PaquetCreateParty(const T *data, size_t len) : Paquet(data, len) { parsePaquet(); }
  virtual ~PaquetCreateParty();

  void			setName(const std::string &);
  const std::string	getName() const;

  void			createPaquet();
  void			parsePaquet();
};

std::ostream	&operator<<(std::ostream &, PaquetCreateParty &);

#endif /* !PAQUETCREATEPARTY_H_ */
