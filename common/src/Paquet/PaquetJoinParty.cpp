//
// PaquetJoinParty.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 15 02:08:19 2015 chapui_s
// Last update Sun Nov 15 02:08:19 2015 chapui_s
//

#include "PaquetJoinParty.hh"

PaquetJoinParty::PaquetJoinParty()
  : _id(Paquet::JOIN_PARTY)
{
}

PaquetJoinParty::PaquetJoinParty(void *data, size_t len)
{
  size_t	ptr = 0;

  writeData<char>(ptr, reinterpret_cast<const char *>(data), len);
  parsePaquet();
}

PaquetJoinParty::PaquetJoinParty(const Buffer &buf)
{
  size_t	ptr = 0;

  writeData<char>(ptr, reinterpret_cast<const char *>(buf.get()), buf.size());
  parsePaquet();
}

PaquetJoinParty::~PaquetJoinParty()
{
}

void			PaquetJoinParty::setName(const std::string &name)
{
  std::string		tmp = name;

  if (tmp.size() > 16) {
    tmp.resize(16);
  }
  _name = tmp;
}

const std::string	PaquetJoinParty::getName() const
{
  return (_name);
}

void			PaquetJoinParty::parsePaquet()
{
  size_t	ptr = 0;
  char		name[17];

  _id = readData<uint8_t>(ptr);

  std::fill(name, name + sizeof(name), 0);
  readData<char>(ptr, name, sizeof(name) - 1);
  _name = name;
}

void			PaquetJoinParty::createPaquet()
{
  size_t	ptr = 0;
  char		name[16];

  writeData<uint8_t>(ptr, &_id);
  std::fill(name, name + sizeof(name), 0);
  std::copy(_name.begin(), _name.end(), name);
  writeData<char>(ptr, name, sizeof(name));
}

std::ostream	&operator<<(std::ostream &os, PaquetJoinParty &p)
{
  p.parsePaquet();
  os << "PaquetJoinParty = { name : '" << p.getName() << "' };" << std::endl;
  return (os);
}
