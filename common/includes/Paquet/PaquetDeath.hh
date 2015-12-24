//
// PaquetDeath.hh for epitech in /home/chapui_s/rendu/
//
// Made by bresci_b
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Dec  9 16:37:07 2015 bresci_b
// Last update Wed Dec  9 16:37:07 2015 bresci_b
//

#ifndef PAQUETDEATH_HH_
# define PAQUETDEATH_HH_

# include "Paquet.hh"

class		PaquetDeath : public Paquet
{
public:
  PaquetDeath();
  PaquetDeath(const Buffer &);
  template <typename T>
  PaquetDeath(const T *data, size_t len) : Paquet(data, len) { parsePaquet(); }
  virtual ~PaquetDeath();

  template <typename T>
  PaquetDeath(const T &p) : _id(Paquet::DEATH) {
    _pID = p->getID();
    createPaquet();
  }

  void		setID(const uint8_t id);
  uint8_t	getID() const;
  void		createPaquet();
  void		parsePaquet();

private:
  uint8_t	_id;
  uint8_t	_pID;
};

std::ostream	&operator<<(std::ostream &, PaquetDeath &);

using PaquetDeath_SharedPtr = std::shared_ptr<PaquetDeath>;

#endif /* !PAQUETDEATH_HH_ */
