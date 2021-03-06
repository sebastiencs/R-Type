
#ifndef PAQUETPLAYERSHOT_H_
# define PAQUETPLAYERSHOT_H_

# include "Paquet.hh"

class		PaquetPlayerShot : public Paquet
{
private:
  uint8_t	_id;
  uint8_t _playerID;
  uint8_t _type;
  uint16_t _x;
  uint16_t _y;
  uint16_t _speed;

public:
  PaquetPlayerShot();
  PaquetPlayerShot(const Buffer &);
  template <typename T>
  PaquetPlayerShot(const T *data, size_t len) : Paquet(data, len) { parsePaquet(); }
  virtual ~PaquetPlayerShot();

  template<typename T>
  PaquetPlayerShot(T &e) : _id(Paquet::PLAYER_SHOT) {
    _playerID = e->getID();
    _type = e->getType();
    _x = e->getX();
    _y = e->getY() + (e->getSizeY() / 2);
    _speed = e->getShotSpeed();
    createPaquet();
  }

  void setType(const uint8_t);
  void setPlayerID(const uint8_t);
  void setPosition(const uint16_t, const uint16_t);
  void setSpeed(uint16_t);

  uint8_t getType() const;
  uint8_t getPlayerID() const;
  uint16_t getX() const;
  uint16_t getY() const;
  uint16_t getSpeed() const;

  void		createPaquet();
  void		parsePaquet();
};

std::ostream	&operator<<(std::ostream &, PaquetPlayerShot &);

using PaquetPlayerShot_SharedPtr = std::shared_ptr<PaquetPlayerShot>;

#endif /* !PAQUETPLAYERSHOT_H_ */
