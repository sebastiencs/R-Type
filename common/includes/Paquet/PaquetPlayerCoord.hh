
#ifndef PAQUETPLAYERCOORD_H_
# define PAQUETPLAYERCOORD_H_

# include "Paquet.hh"

class		PaquetPlayerCoord : public Paquet
{
private:
  uint8_t	_id;
  uint8_t _playerID;
  uint16_t _x;
  uint16_t _y;

public:
  PaquetPlayerCoord();
  PaquetPlayerCoord(const Buffer &);
  template <typename T>
  PaquetPlayerCoord(const T *data, size_t len) : Paquet(data, len) { parsePaquet(); }
  virtual ~PaquetPlayerCoord();

  void setPlayerID(const uint8_t&);
  void setPosition(const uint16_t&, const uint16_t&);

  const uint8_t& getPlayerID() const;
  const uint16_t& getX() const;
  const uint16_t& getY() const;

  void		createPaquet();
  void		parsePaquet();
};

std::ostream	&operator<<(std::ostream &, PaquetPlayerCoord &);

#endif /* !PAQUETPLAYERCOORD_H_ */
