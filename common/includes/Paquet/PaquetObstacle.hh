
#ifndef PAQUETOBSTACLE_H_
# define PAQUETOBSTACLE_H_

# include "Paquet.hh"

class		PaquetObstacle : public Paquet
{
private:
  uint8_t	_id;
  uint8_t _type;
  uint16_t _x;
  uint16_t _y;

public:
  PaquetObstacle();
  PaquetObstacle(const Buffer &);
  template <typename T>
  PaquetObstacle(const T *data, size_t len) : Paquet(data, len) { parsePaquet(); }
  virtual ~PaquetObstacle();

  void setType(const uint8_t&);
  void setPosition(const uint16_t&, const uint16_t&);

  const uint8_t& getType() const;
  const uint16_t& getX() const;
  const uint16_t& getY() const;

  void		createPaquet();
  void		parsePaquet();
};

std::ostream	&operator<<(std::ostream &, PaquetObstacle &);

#endif /* !PAQUETOBSTACLE_H_ */
