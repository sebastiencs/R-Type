//
// PaquetListParties.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sat Nov 14 05:00:44 2015 chapui_s
// Last update Sat Nov 14 05:00:44 2015 chapui_s
//

#ifndef PAQUETLISTPARTIES_H_
# define PAQUETLISTPARTIES_H_

# include <list>
# include <tuple>
# include "Paquet.hh"

typedef std::tuple<std::string, uint8_t>	PartyNB;

class		PaquetListParties : public Paquet
{
private:
  uint8_t		_id;
  uint16_t		_nbParties;
  std::list<PartyNB>	_listParties;

public:
  PaquetListParties();
  PaquetListParties(const Buffer &);
  template <typename T>
  PaquetListParties(const T *data, size_t len)
    : Paquet(data, len) { parsePaquet(); }
  virtual ~PaquetListParties();

  void		addParty(const std::string &, uint8_t);

  const std::list<PartyNB>	&getParties() const;

  void		createPaquet();
  void		parsePaquet();
};

std::ostream	&operator<<(std::ostream &, PaquetListParties &);

using PaquetListParties_SharedPtr = std::shared_ptr<PaquetListParties>;

#endif /* !PAQUETLISTPARTIES_H_ */
