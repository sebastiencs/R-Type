//
// PaquetEnemy.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Dec  9 16:37:07 2015 chapui_s
// Last update Wed Dec  9 16:37:07 2015 chapui_s
//

#ifndef PAQUETENEMY_H_
# define PAQUETENEMY_H_

# include "Paquet.hh"

class		PaquetEnemy : public Paquet
{
private:
  uint8_t	_id;
  uint8_t	_type;
  uint8_t	_eID;
  uint16_t	_x;
  uint16_t	_y;
  uint8_t	_life;

public:
  PaquetEnemy();
  PaquetEnemy(const Buffer &);
  template <typename T>
  PaquetEnemy(const T *data, size_t len) : Paquet(data, len) { parsePaquet(); }
  virtual ~PaquetEnemy();

  void	setType(const uint8_t);
  void	setID(const uint8_t);
  void	setPosition(const uint16_t, const uint16_t);
  void	setLife(const uint8_t);

  uint8_t	getType() const;
  uint8_t	getID() const;
  uint16_t	getX() const;
  uint16_t	getY() const;
  uint8_t	getLife() const;

  void		createPaquet();
  void		parsePaquet();
};

std::ostream	&operator<<(std::ostream &, PaquetEnemy &);

#endif /* !PAQUETENEMY_H_ */
