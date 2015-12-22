//
// PaquetAttrBonus.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Dec 23 00:50:02 2015 chapui_s
// Last update Wed Dec 23 00:50:02 2015 chapui_s
//

#include "PaquetAttrBonus.hh"

PaquetAttrBonus::PaquetAttrBonus()
  : _id(Paquet::ATTR_BONUS)
{
}

PaquetAttrBonus::PaquetAttrBonus(const Buffer &buf)
{
  size_t	ptr = 0;

  writeData(ptr, buf.get(), buf.size());
  parsePaquet();
}

PaquetAttrBonus::~PaquetAttrBonus()
{
}

void		PaquetAttrBonus::setID(const uint8_t id)
{
  _pID = id;
}

void		PaquetAttrBonus::setTime(const uint16_t time)
{
  _time = time;
}

uint8_t		PaquetAttrBonus::getID() const
{
  return _pID;
}

uint16_t	PaquetAttrBonus::getTime() const
{
  return _time;
}

void		PaquetAttrBonus::parsePaquet()
{
  size_t	ptr = 0;

  _id = readData<uint8_t>(ptr);
  _pID = readData<uint8_t>(ptr);
  _time = readData<uint16_t>(ptr);
}

void		PaquetAttrBonus::createPaquet()
{
  size_t	ptr = 0;

  writeData<uint8_t>(ptr, &_id);
  writeData<uint8_t>(ptr, &_pID);
  writeData<uint16_t>(ptr, &_time);
}

std::ostream	&operator<<(std::ostream &os, PaquetAttrBonus &p)
{
  p.parsePaquet();
  os << "PaquetAttrBonus = "
     << " { ID : " << (int)p.getID()
     << ", Time : " << (int)p.getTime()
     << " };";
  return (os);
}
