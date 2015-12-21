//
// PaquetCreateParty.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 15 02:08:19 2015 chapui_s
// Last update Sun Nov 15 02:08:19 2015 chapui_s
//

#include "PaquetCreateParty.hh"

PaquetCreateParty::PaquetCreateParty()
  : _id(Paquet::CREATE_PARTY)
{
}

PaquetCreateParty::PaquetCreateParty(const Buffer &buf)
{
  size_t	ptr = 0;

  writeData(ptr, buf.get(), buf.size());
  parsePaquet();
}

PaquetCreateParty::~PaquetCreateParty()
{
}

void			PaquetCreateParty::setName(const std::string &name)
{
  std::string		tmp = name;

  if (tmp.size() > 16) {
    tmp.resize(16);
  }
  _name = tmp;
}

const std::string	PaquetCreateParty::getName() const
{
  return (_name);
}

void			PaquetCreateParty::parsePaquet()
{
  size_t	ptr = 0;
  char		name[17];

  _id = readData<uint8_t>(ptr);

  std::fill(name, name + sizeof(name), 0);
  readData<char>(ptr, name, sizeof(name) - 1);
  _name = name;
}

void			PaquetCreateParty::createPaquet()
{
  size_t	ptr = 0;
  char		name[16];

  writeData<uint8_t>(ptr, &_id);
  std::fill(name, name + sizeof(name), 0);
  std::copy(_name.begin(), _name.end(), name);
  writeData<char>(ptr, name, sizeof(name));
}

std::ostream	&operator<<(std::ostream &os, PaquetCreateParty &p)
{
  p.parsePaquet();
  os << "PaquetCreateParty = { name : '" << p.getName() << "' };";
  return (os);
}
