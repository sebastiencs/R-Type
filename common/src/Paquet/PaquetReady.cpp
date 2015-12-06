//
// PaquetReady.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 15 22:54:33 2015 chapui_s
// Last update Sun Nov 15 22:54:33 2015 chapui_s
//

#include "PaquetReady.hh"

PaquetReady::PaquetReady()
  : _id(Paquet::READY)
{
}

PaquetReady::PaquetReady(const Buffer &buf)
{
  size_t	ptr = 0;

  writeData<char>(ptr, reinterpret_cast<const char *>(buf.get()), buf.size());
  parsePaquet();
}

PaquetReady::~PaquetReady()
{
}

void			PaquetReady::setID(uint8_t id)
{
  _playerID = id;
}

uint8_t			PaquetReady::getID() const
{
  return (_playerID);
}

void			PaquetReady::setStatus(uint8_t status)
{
  _status = status;
}

uint8_t PaquetReady::getID() const
{
	return _playerID;
}

uint8_t			PaquetReady::getStatus() const
{
  return (_status);
}

void			PaquetReady::parsePaquet()
{
  size_t	ptr = 0;

  _id = readData<uint8_t>(ptr);
  _playerID = readData<uint8_t>(ptr);
  _status = readData<uint8_t>(ptr);
}

void			PaquetReady::createPaquet()
{
  size_t	ptr = 0;

  writeData<uint8_t>(ptr, &_id);
  writeData<uint8_t>(ptr, &_playerID);
  writeData<uint8_t>(ptr, &_status);
}

std::ostream	&operator<<(std::ostream &os, PaquetReady &p)
{
  p.parsePaquet();

  int		playerID = p.getID();
  int		status = p.getStatus();

  os << "PaquetReady = { playerID : " << playerID << ", status : " << status << " };";
  return (os);
}
