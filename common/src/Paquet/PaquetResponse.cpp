//
// PaquetResponse.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Fri Nov 13 21:47:15 2015 chapui_s
// Last update Fri Nov 13 21:47:15 2015 chapui_s
//

#include "PaquetResponse.hh"

PaquetResponse::PaquetResponse()
  : _id(Paquet::RESPONSE)
{
}

PaquetResponse::PaquetResponse(void *data, size_t len)
{
  size_t	ptr = 0;

  writeData<char>(ptr, reinterpret_cast<const char *>(data), len);
}

PaquetResponse::~PaquetResponse()
{
}

void			PaquetResponse::setReturn(uint8_t ret)
{
  _return = ret;
}

void			PaquetResponse::setData(uint32_t data)
{
  _data = data;
}

uint8_t			PaquetResponse::getReturn() const
{
  return (_return);
}

uint32_t		PaquetResponse::getData() const
{
  return (_data);
}

void			PaquetResponse::parsePaquet()
{
  size_t	ptr = 0;

  _id = readData<uint8_t>(ptr);
  _return = readData<uint8_t>(ptr);
  _data = readData<uint32_t>(ptr);
}

void			PaquetResponse::createPaquet()
{
  size_t	ptr = 0;

  writeData<uint8_t>(ptr, &_id);
  writeData<uint8_t>(ptr, &_return);
  writeData<uint32_t>(ptr, &_data);
}

std::ostream	&operator<<(std::ostream &os, PaquetResponse &p)
{
  p.parsePaquet();
  os << "PaquetResponse = { return : " << p.getReturn()
     << ", data : '" << p.getData()
     << " };" << std::endl;
  return (os);
}
