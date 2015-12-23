//
// PaquetLaunch.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 15 22:58:38 2015 chapui_s
// Last update Sun Nov 15 22:58:38 2015 chapui_s
//

#ifndef PAQUETLAUNCH_H_

# define PAQUETLAUNCH_H_
# include "Paquet.hh"

class		PaquetLaunch : public Paquet
{
private:
  uint8_t	_id;

public:
  PaquetLaunch();
  PaquetLaunch(const Buffer &);
  template <typename T>
  PaquetLaunch(const T *data, size_t len) : Paquet(data, len) { parsePaquet(); }
  virtual ~PaquetLaunch();

  void		createPaquet();
  void		parsePaquet();
};

std::ostream	&operator<<(std::ostream &, PaquetLaunch &);

using PaquetLaunch_SharedPtr = std::shared_ptr<PaquetLaunch>;

#endif /* !PAQUETLAUNCH_H_ */
