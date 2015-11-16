//
// PaquetListParties.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sat Nov 14 05:06:59 2015 chapui_s
// Last update Sat Nov 14 05:06:59 2015 chapui_s
//

#include <algorithm>
#include "PaquetListParties.hh"

PaquetListParties::PaquetListParties()
  : _id(Paquet::LIST_PARTIES)
{
}

PaquetListParties::PaquetListParties(void *data, size_t len)
{
  size_t	ptr = 0;

  writeData<char>(ptr, reinterpret_cast<const char *>(data), len);
  parsePaquet();
}

PaquetListParties::~PaquetListParties()
{
}

void			PaquetListParties::addParty(const std::string &name, uint8_t n)
{
  std::string		tmp = name;

  if (tmp.size() > 16) {
    tmp.resize(16);
  }

  std::tuple<std::string, uint8_t>	tuple(tmp, n);
  _listParties.push_back(tuple);
}

const std::list<std::tuple<std::string, uint8_t>>	&PaquetListParties::getParties() const
{
  return (_listParties);
}

void			PaquetListParties::parsePaquet()
{
  size_t	ptr = 0;

  _listParties.clear();

  _id = readData<uint8_t>(ptr);
  _nbParties = readData<uint16_t>(ptr);

  for (uint16_t i = 0; i < _nbParties; i += 1) {

    char		name[17];
    uint8_t		nb;

    std::fill(name, name + sizeof(name), 0);
    readData<char>(ptr, name, sizeof(name) - 1);

    nb = readData<uint8_t>(ptr);

    _listParties.push_back(std::make_tuple(name, nb));
  }
}

void			PaquetListParties::createPaquet()
{
  size_t	ptr = 0;
  uint16_t	nb = (uint16_t)_listParties.size();

  writeData<uint8_t>(ptr, &_id);
  writeData<uint16_t>(ptr, &nb);

  for (auto party : _listParties) {

    char	nameChar[16];
    std::string	name(std::get<0>(party));

    std::fill(nameChar, nameChar + sizeof(nameChar), 0);
    std::copy(name.begin(), name.end(), nameChar);
    writeData<char>(ptr, (char *)nameChar, sizeof(nameChar));

    uint8_t	size = std::get<1>(party);
    writeData<uint8_t>(ptr, &size);
  }
}

std::ostream	&operator<<(std::ostream &os, PaquetListParties &p)
{
  p.parsePaquet();

  std::list<std::tuple<std::string, uint8_t>>	list = p.getParties();

  os << "PaquetListParties = " << std::endl
     << " { nb Parties : " << list.size() << std::endl;
  for (auto party : list) {
    std::string name(std::get<0>(party));
    os << "\t{ name : '" << name
       << "', nb : " << (int)std::get<1>(party)
       << " }" << std::endl;
  }
  os << " };" << std::endl;
  return (os);
}
