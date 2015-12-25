#ifndef PAQUETCHAT_H_
# define PAQUETCHAT_H_

# include "Paquet.hh"

class		PaquetChat : public Paquet
{
public:
  PaquetChat();
  PaquetChat(const Buffer &);
  template <typename T>
  PaquetChat(const T *data, size_t len) : Paquet(data, len) { parsePaquet(); }
  virtual ~PaquetChat();

  void			setID(const uint8_t pID);
  uint8_t		getID() const;

  void			setMessage(const std::string &);
  const std::string	getMessage() const;

  void			createPaquet();
  void			parsePaquet();

private:
  uint8_t	_id;
  uint8_t	_pID;
  char		_message[32];

};

std::ostream	&operator<<(std::ostream &, PaquetChat &);

using PaquetChat_SharedPtr = std::shared_ptr<PaquetChat>;

#endif /* !PAQUETCHAT_H_ */
