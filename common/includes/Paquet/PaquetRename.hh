#ifndef PAQUETRENAME_H_
# define PAQUETRENAME_H_

# include "Paquet.hh"

class		PaquetRename : public Paquet
{
public:
  PaquetRename();
  PaquetRename(const Buffer &);
  template <typename T>
  PaquetRename(const T *data, size_t len) : Paquet(data, len) { parsePaquet(); }
  virtual ~PaquetRename();

  void			setID(const uint8_t pID);
  uint8_t		getID() const;

  void			setName(const std::string &);
  const std::string	getName() const;

  void			createPaquet();
  void			parsePaquet();

private:
  uint8_t	_id;
  uint8_t	_pID;
  char		_name[16];

};

std::ostream	&operator<<(std::ostream &, PaquetRename &);

using PaquetRename_SharedPtr = std::shared_ptr<PaquetRename>;

#endif /* !PAQUETRENAME_H_ */
