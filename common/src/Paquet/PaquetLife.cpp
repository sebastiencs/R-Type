//
// PaquetLife.hh for epitech in /home/chapui_s/rendu/
//
// Made by bresci_b
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Dec  9 16:37:07 2015 bresci_b
// Last update Wed Dec  9 16:37:07 2015 bresci_b
//

#include "PaquetLife.hh"

PaquetLife::PaquetLife()
  : _id(Paquet::LIFE)
{
}

PaquetLife::PaquetLife(const Buffer &buf)
{
  size_t	ptr = 0;
  
  writeData<char>(ptr, reinterpret_cast<const char *>(buf.get()), buf.size());
  parsePaquet();
}

PaquetLife::~PaquetLife()
{
}

void		PaquetLife::setID(const uint8_t id)
{
  _pID = id;
}

void		PaquetLife::setLife(const uint8_t life)
{
  _life = life;
}

uint8_t		PaquetLife::getID() const
{
  return _pID;
}

uint8_t	        PaquetLife::getLife() const
{
  return _life;
}

void		PaquetLife::parsePaquet()
{
  size_t	ptr = 0;

  _id = readData<uint8_t>(ptr);
  _pID = readData<uint8_t>(ptr);
  _life = readData<uint8_t>(ptr);
}

void		PaquetLife::createPaquet()
{
  size_t	ptr = 0;

  writeData<uint8_t>(ptr, &_id);
  writeData<uint8_t>(ptr, &_pID);
  writeData<uint8_t>(ptr, &_life);
}

std::ostream	&operator<<(std::ostream &os, PaquetLife &p)
{
  p.parsePaquet();
  os << "PaquetLife = "
     << " { ID : " << (int)p.getID()
     << ", Life : " << (int)p.getLife()
     << " };";
  return (os);
}
