//
// PaquetFirst.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Fri Nov 13 21:47:15 2015 chapui_s
// Last update Fri Nov 13 21:47:15 2015 chapui_s
//

#include "PaquetFirst.hh"

PaquetFirst::PaquetFirst()
  : _id(Paquet::FIRST),
    _version(0),
    _name(),
    _level(0)
{
}

PaquetFirst::PaquetFirst(void *data, size_t len)
{
  size_t	ptr = 0;

  writeData<char>(ptr, reinterpret_cast<const char *>(data), len);
}

PaquetFirst::~PaquetFirst()
{
}

void			PaquetFirst::setVersion(uint16_t version)
{
  _version = version;
}

void			PaquetFirst::setName(const std::string &name)
{
  size_t		len = name.size();

  if (len > sizeof(_name)) {
    len = sizeof(_name);
  }
  std::copy(name.c_str(), name.c_str() + len, _name);
}

void			PaquetFirst::setLevel(uint8_t level)
{
  _level = level;
}

uint16_t		PaquetFirst::getVersion() const
{
  return (_version);
}

const std::string	PaquetFirst::getName() const
{
  return (_name);
}

uint8_t			PaquetFirst::getLevel() const
{
  return (_level);
}

void			PaquetFirst::parsePaquet()
{
  size_t	ptr = 0;

  _id = readData<uint8_t>(ptr);
  _version = readData<uint16_t>(ptr);
  readData<char>(ptr, _name, sizeof(_name));
  _level = readData<uint8_t>(ptr);
}

void			PaquetFirst::createPaquet()
{
  size_t	ptr = 0;

  writeData<uint8_t>(ptr, &_id);
  writeData<uint16_t>(ptr, &_version);
  writeData<char>(ptr, _name, sizeof(_name));
  writeData<uint8_t>(ptr, &_level);
}

std::ostream	&operator<<(std::ostream &os, PaquetFirst &p)
{
  p.parsePaquet();

  int		version = p.getVersion();
  int		level = p.getLevel();

  os << "PaquetFirst = { version : " << version
     << ", name : '" << p.getName()
     << "', level : " << level
     << " };" << std::endl;
  return (os);
}
