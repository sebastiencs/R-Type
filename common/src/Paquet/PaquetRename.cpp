
#include "PaquetRename.hh"

PaquetRename::PaquetRename()
  : _id(Paquet::RENAME)
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
  std::string		tmp = name;

  if (tmp.size() > 16) {
    tmp.resize(16);
  }
  _name = tmp;
}

const std::string	PaquetRename::getName() const
{
  return (_name);
}

void			PaquetRename::parsePaquet()
{
  size_t	ptr = 0;
  char		name[17];

  _id = readData<uint8_t>(ptr);
  _pID = readData<uint8_t>(ptr);
  std::fill(name, name + sizeof(name), 0);
  readData<char>(ptr, name, sizeof(name) - 1);
  _name = name;
}

void			PaquetRename::createPaquet()
{
  size_t	ptr = 0;
  char		name[16];

  writeData<uint8_t>(ptr, &_id);
  writeData<uint8_t>(ptr, &_pID);
  std::fill(name, name + sizeof(name), 0);
  std::copy(_name.begin(), _name.end(), name);
  writeData<char>(ptr, name, sizeof(name));
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
