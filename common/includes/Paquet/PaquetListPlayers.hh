//
// PaquetListPlayers.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sat Nov 14 05:00:44 2015 chapui_s
// Last update Sat Nov 14 05:00:44 2015 chapui_s
//

#ifndef PAQUETLISTPLAYERS_H_
# define PAQUETLISTPLAYERS_H_

# include <list>
# include <tuple>
# include "Paquet.hh"

typedef std::tuple<std::string, uint8_t, uint8_t>	PlayerIDLevel;

class		PaquetListPlayers : public Paquet
{
private:
  uint8_t			_id;
  uint8_t			_nbPlayers;
  std::list<PlayerIDLevel>	_listPlayers;

public:
  PaquetListPlayers();
  PaquetListPlayers(const Buffer &);
  template <typename T>
  PaquetListPlayers(const T *data, size_t len) : Paquet(data, len) { parsePaquet(); }
  virtual ~PaquetListPlayers();

  template<typename T>
  PaquetListPlayers(T &list) : _id(Paquet::LIST_PLAYERS) {
    list.for_each([&] (auto &e) {
	this->addPlayer(e->getName(), e->getID(), e->getLevel());
      });
    createPaquet();
  }

  template<typename T>
  PaquetListPlayers &operator=(T &list) {
    list.for_each([&] (auto &e) {
	this->addPlayer(e->getName(), e->getID(), e->getLevel());
      });
    createPaquet();
    return (*this);
  }

  void		addPlayer(const std::string &, uint8_t, uint8_t);

  const std::list<PlayerIDLevel>	&getPlayers() const;

  void		createPaquet();
  void		parsePaquet();
};

std::ostream	&operator<<(std::ostream &, PaquetListPlayers &);

using PaquetListPlayers_SharedPtr = std::shared_ptr<PaquetListPlayers>;

#endif /* !PAQUETLISTPLAYERS_H_ */
