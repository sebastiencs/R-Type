//
// PaquetDeath.hh for epitech in /home/chapui_s/rendu/
//
// Made by bresci_b
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Dec  9 16:37:07 2015 bresci_b
// Last update Wed Dec  9 16:37:07 2015 bresci_b
//

#include "PaquetDeath.hh"

PaquetDeath::PaquetDeath()
  : _id(Paquet::DEATH)
{
}

PaquetDeath::PaquetDeath(const Buffer &buf)
{
  size_t	ptr = 0;

  writeData(ptr, buf.get(), buf.size());
  parsePaquet();
}

PaquetDeath::~PaquetDeath()
{
}

void		PaquetDeath::setID(const uint8_t id)
{
  _pID = id;
}

uint8_t		PaquetDeath::getID() const
{
  return _pID;
}

void		PaquetDeath::parsePaquet()
{
  size_t	ptr = 0;

  _id = readData<uint8_t>(ptr);
  _pID = readData<uint8_t>(ptr);
}

void		PaquetDeath::createPaquet()
{
  size_t	ptr = 0;

  writeData<uint8_t>(ptr, &_id);
  writeData<uint8_t>(ptr, &_pID);
}

std::ostream	&operator<<(std::ostream &os, PaquetDeath &p)
{
  p.parsePaquet();
  os << "PaquetDeath = "
     << " { ID : " << (int)p.getID()
     << " };";
  return (os);
}
