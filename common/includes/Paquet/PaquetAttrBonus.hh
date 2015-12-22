//
// PaquetAttrBonus.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Dec 23 00:50:14 2015 chapui_s
// Last update Wed Dec 23 00:50:14 2015 chapui_s
//

#ifndef PAQUETATTRBONUS_HH_
# define PAQUETATTRBONUS_HH_

# include "Paquet.hh"

class		PaquetAttrBonus : public Paquet
{
public:
  PaquetAttrBonus();
  PaquetAttrBonus(const Buffer &);
  template <typename T>
  PaquetAttrBonus(const T *data, size_t len) : Paquet(data, len) { parsePaquet(); }
  virtual ~PaquetAttrBonus();

  template <typename T>
  PaquetAttrBonus(const T &p) : _id(Paquet::ATTR_BONUS) {
    _pID = p->getID();
    _time = p->getTime();
    createPaquet();
  }

  void		setID(const uint8_t id);
  void		setTime(const uint16_t time);
  uint8_t	getID() const;
  uint16_t	getTime() const;
  void		createPaquet();
  void		parsePaquet();

private:
  uint8_t	_id;
  uint8_t	_pID;
  uint16_t	_time;
};

std::ostream	&operator<<(std::ostream &, PaquetAttrBonus &);

#endif /* !PAQUETATTRBONUS_HH_ */
