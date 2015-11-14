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

  bool		_parsed;

public:
  PaquetFirst();
  PaquetFirst(void *, size_t);
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

template<typename T>
T		&operator<<(T &s, PaquetFirst &p)
{
  p.createPaquet();
  s.write(reinterpret_cast<const char *>(p.getData()), p.getSize());
  return (s);
}

template<typename T>
T		*operator<<(T *s, PaquetFirst &p)
{
  p.createPaquet();
  s->write(reinterpret_cast<const char *>(p.getData()), p.getSize());
  return (s);
}

#endif /* !PAQUETFIRST_H_ */
