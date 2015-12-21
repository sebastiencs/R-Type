//
// PaquetListPlayers.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sat Nov 14 05:06:59 2015 chapui_s
// Last update Sat Nov 14 05:06:59 2015 chapui_s
//

#include <algorithm>
#include "PaquetListPlayers.hh"

PaquetListPlayers::PaquetListPlayers()
  : _id(Paquet::LIST_PLAYERS)
{
  createPaquet();
}

PaquetListPlayers::PaquetListPlayers(const Buffer &buf)
{
  size_t	ptr = 0;

  writeData(ptr, buf.get(), buf.size());
  parsePaquet();
}

PaquetListPlayers::~PaquetListPlayers()
{
}

void			PaquetListPlayers::addPlayer(const std::string &name, uint8_t id, uint8_t level)
{
  std::string		tmp = name;

  if (tmp.size() > 16) {
    tmp.resize(16);
  }

  PlayerIDLevel		tuple(tmp, id, level);
  _listPlayers.push_back(tuple);
}

const std::list<PlayerIDLevel>	&PaquetListPlayers::getPlayers() const
{
  return (_listPlayers);
}

void			PaquetListPlayers::parsePaquet()
{
  size_t	ptr = 0;

  _listPlayers.clear();

  _id = readData<uint8_t>(ptr);
  _nbPlayers = readData<uint8_t>(ptr);

  for (uint8_t i = 0; i < _nbPlayers; i += 1) {

    char		name[17];
    uint8_t		id;
    uint8_t		level;

    std::fill(name, name + sizeof(name), 0);
    readData<char>(ptr, name, sizeof(name) - 1);

    id = readData<uint8_t>(ptr);
    level = readData<uint8_t>(ptr);

    _listPlayers.push_back(std::make_tuple(name, id, level));
  }
}

void			PaquetListPlayers::createPaquet()
{
  size_t	ptr = 0;
  uint8_t	nb = (uint8_t)_listPlayers.size();

  writeData<uint8_t>(ptr, &_id);
  writeData<uint8_t>(ptr, &nb);

  for (auto player : _listPlayers) {

    char	nameChar[16];
    std::string	name(std::get<0>(player));

    std::fill(nameChar, nameChar + sizeof(nameChar), 0);
    std::copy(name.begin(), name.end(), nameChar);
    writeData<char>(ptr, (char *)nameChar, sizeof(nameChar));

    uint8_t	id = std::get<1>(player);
    writeData<uint8_t>(ptr, &id);

    uint8_t	level = std::get<2>(player);
    writeData<uint8_t>(ptr, &level);
  }
}

std::ostream	&operator<<(std::ostream &os, PaquetListPlayers &p)
{
  p.parsePaquet();

  std::list<PlayerIDLevel>	list = p.getPlayers();

  os << "PaquetListPlayers = " << std::endl
     << " { nb Players : " << list.size() << std::endl;
  for (auto player : list) {
    std::string name(std::get<0>(player));
    os << "\t{ name : '" << name
       << "', id : " << (int)std::get<1>(player)
       << ", level : " << (int)std::get<2>(player)
       << " }" << std::endl;
  }
  os << " };";
  return (os);
}
