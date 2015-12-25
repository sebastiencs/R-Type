
#include "PaquetRename.hh"

PaquetRename::PaquetRename()
  : _id(Paquet::RENAME), _name()
{
}

PaquetRename::PaquetRename(const Buffer &buf)
{
  size_t	ptr = 0;

  writeData(ptr, buf.get(), buf.size());
  parsePaquet();
}

PaquetRename::~PaquetRename()
{
}

void			PaquetRename::setID(const uint8_t pID)
{
  _pID = pID;
}


uint8_t			PaquetRename::getID() const
{
  return _pID;
}

void			PaquetRename::setName(const std::string &name)
{
  size_t		len = name.size();

  if (len > sizeof(_name)) {
    len = sizeof(_name);
  }
  std::copy(name.c_str(), name.c_str() + len, _name);
}

const std::string	PaquetRename::getName() const
{
  return (_name);
}

void			PaquetRename::parsePaquet()
{
  size_t	ptr = 0;

  _id = readData<uint8_t>(ptr);
  _pID = readData<uint8_t>(ptr);
  readData<char>(ptr, _name, sizeof(_name));
}

void			PaquetRename::createPaquet()
{
  size_t	ptr = 0;

  writeData<uint8_t>(ptr, &_id);
  writeData<uint8_t>(ptr, &_pID);
  writeData<char>(ptr, _name, sizeof(_name));
}

std::ostream	&operator<<(std::ostream &os, PaquetRename &p)
{
  p.parsePaquet();
  os << "PaquetRename = { name : "
     << p.getName()
     << ", PlayerID : "
     << static_cast<int>(p.getID())
     << " };";
  return (os);
}
