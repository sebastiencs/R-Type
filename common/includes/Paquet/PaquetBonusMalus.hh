//
// PaquetBonusMalus.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sat Dec 12 02:19:42 2015 chapui_s
// Last update Sat Dec 12 02:19:42 2015 chapui_s
//

#ifndef PAQUETBONUSMALUS_H_
# define PAQUETBONUSMALUS_H_

# include "Paquet.hh"

class		PaquetBonusMalus : public Paquet
{
private:
  uint8_t	_id;
  uint8_t	_type;
  uint8_t	_eID;
  uint16_t	_x;
  uint16_t	_y;
  uint8_t	_speed;

public:
  PaquetBonusMalus();
  PaquetBonusMalus(const Buffer &);
  template <typename T>
  PaquetBonusMalus(const T *data, size_t len) : Paquet(data, len) { parsePaquet(); }
  virtual ~PaquetBonusMalus();

  template<typename T>
  PaquetBonusMalus &operator=(T &e) {
    if (e) {
      _type = e->getType();
      _eID = e->getID();
      _x = e->getX();
      _y = e->getY();
      _type = e->getType();
      _speed = e->getSpeed();
      createPaquet();
    }
    return (*this);
  }

  void	setType(const uint8_t);
  void	setID(const uint8_t);
  void	setPosition(const uint16_t, const uint16_t);
  void	setSpeed(const uint8_t);

  uint8_t	getType() const;
  uint8_t	getID() const;
  uint16_t	getX() const;
  uint16_t	getY() const;
  uint8_t	getSpeed() const;

  void		createPaquet();
  void		parsePaquet();
};

std::ostream	&operator<<(std::ostream &, PaquetBonusMalus &);

using PaquetBonusMalus_SharedPtr = std::shared_ptr<PaquetBonusMalus>;

#endif /* !PAQUETBONUSMALUS_H_ */
