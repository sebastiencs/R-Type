//
// PaquetLaunch.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 15 22:59:46 2015 chapui_s
// Last update Sun Nov 15 22:59:46 2015 chapui_s
//

#include "PaquetLaunch.hh"

PaquetLaunch::PaquetLaunch()
  : _id(Paquet::LAUNCH)
{
  createPaquet();
}

PaquetLaunch::PaquetLaunch(const Buffer &buf)
{
  size_t	ptr = 0;

  writeData<char>(ptr, reinterpret_cast<const char *>(buf.get()), buf.size());
  parsePaquet();
}

PaquetLaunch::~PaquetLaunch()
{
}

void			PaquetLaunch::parsePaquet()
{
  size_t	ptr = 0;

  _id = readData<uint8_t>(ptr);
}

void			PaquetLaunch::createPaquet()
{
  size_t	ptr = 0;

  writeData<uint8_t>(ptr, &_id);
}

std::ostream	&operator<<(std::ostream &os, PaquetLaunch &p)
{
  p.parsePaquet();
  os << "PaquetLaunch = {};";
  return (os);
}
