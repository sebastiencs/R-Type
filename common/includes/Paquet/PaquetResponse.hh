//
// PaquetResponse.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Fri Nov 13 21:34:17 2015 chapui_s
// Last update Fri Nov 13 21:34:17 2015 chapui_s
//

#ifndef PAQUETRESPONSE_H_
# define PAQUETRESPONSE_H_

# include "Paquet.hh"

class		PaquetResponse : public Paquet
{
private:
  uint8_t	_id;
  uint8_t	_return;
  uint32_t	_data;

public:
  PaquetResponse();
  PaquetResponse(const Buffer &);
  template <typename T>
  PaquetResponse(const T *data, size_t len) : Paquet(data, len) { }
  virtual ~PaquetResponse();

  void		setReturn(uint8_t);
  void		setData(uint32_t);

  uint8_t	getReturn() const;
  uint32_t	getData() const;

  void		createPaquet();
  void		parsePaquet();
};

std::ostream	&operator<<(std::ostream &, PaquetResponse &);

#endif /* !PAQUETRESPONSE_H_ */
