//
// PaquetFirst.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Fri Nov 13 21:34:17 2015 chapui_s
// Last update Fri Nov 13 21:34:17 2015 chapui_s
//

#ifndef PAQUETFIRST_H_
# define PAQUETFIRST_H_

# include "Paquet.hh"

class		PaquetFirst : public Paquet
{
private:
  uint8_t	_id;
  uint16_t	_version;
  char		_name[16];
  uint8_t	_level;

public:
  PaquetFirst();
  PaquetFirst(const Buffer &);
  template <typename T>
  PaquetFirst(const T *data, size_t len) : Paquet(data, len) { parsePaquet(); }
  virtual ~PaquetFirst();

  void		setVersion(uint16_t);
  void		setName(const std::string &);
  void		setLevel(uint8_t);

  uint16_t		getVersion() const;
  const std::string	getName() const;
  uint8_t		getLevel() const;

  void		createPaquet();
  void		parsePaquet();
};

std::ostream	&operator<<(std::ostream &, PaquetFirst &);

#endif /* !PAQUETFIRST_H_ */
