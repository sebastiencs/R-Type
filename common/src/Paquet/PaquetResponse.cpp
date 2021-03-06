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
  : _id(Paquet::RESPONSE),
    _return(0),
    _data(0)
{
}

PaquetResponse::PaquetResponse(const Buffer &buf)
{
  size_t	ptr = 0;

  writeData(ptr, buf.get(), buf.size());
  parsePaquet();
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
  os << "PaquetResponse = { return : " << (int)p.getReturn()
     << ", data : '" << p.getData()
     << " };";
  return (os);
}
