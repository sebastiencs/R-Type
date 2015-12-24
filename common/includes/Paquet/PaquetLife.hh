//
// PaquetLife.hh for epitech in /home/chapui_s/rendu/
//
// Made by bresci_b
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Dec  9 16:37:07 2015 bresci_b
// Last update Wed Dec  9 16:37:07 2015 bresci_b
//

#ifndef PAQUETLIFE_HH_
# define PAQUETLIFE_HH_

# include "Paquet.hh"

class		PaquetLife : public Paquet
{
public:
  PaquetLife();
  PaquetLife(const Buffer &);
  template <typename T>
  PaquetLife(const T *data, size_t len) : Paquet(data, len) { parsePaquet(); }
  virtual ~PaquetLife();

  template <typename T>
  PaquetLife(const T &p) : _id(Paquet::LIFE) {
    _pID = p->getID();
    _life = p->getLife();
    createPaquet();
  }

  void		setID(const uint8_t id);
  void		setLife(const uint8_t life);
  uint8_t	getID() const;
  uint8_t	getLife() const;
  void		createPaquet();
  void		parsePaquet();

private:
  uint8_t	_id;
  uint8_t	_pID;
  uint8_t	_life;
};

std::ostream	&operator<<(std::ostream &, PaquetLife &);

using PaquetLife_SharedPtr = std::shared_ptr<PaquetLife>;

#endif /* !PAQUETLIFE_HH_ */
