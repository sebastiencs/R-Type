
#include "PaquetChat.hh"

PaquetChat::PaquetChat()
  : _id(Paquet::CHAT), _message()
{
}

PaquetChat::PaquetChat(const Buffer &buf)
{
  size_t	ptr = 0;

  writeData(ptr, buf.get(), buf.size());
  parsePaquet();
}

PaquetChat::~PaquetChat()
{
}

void			PaquetChat::setID(const uint8_t pID)
{
  _pID = pID;
}


uint8_t			PaquetChat::getID() const
{
  return _pID;
}

void			PaquetChat::setMessage(const std::string &name)
{
  size_t		len = name.size();

  if (len > sizeof(_message)) {
    len = sizeof(_message);
  }
  std::copy(name.c_str(), name.c_str() + len, _message);
}

const std::string	PaquetChat::getMessage() const
{
  return (_message);
}

void			PaquetChat::parsePaquet()
{
  size_t	ptr = 0;

  _id = readData<uint8_t>(ptr);
  _pID = readData<uint8_t>(ptr);
  readData<char>(ptr, _message, sizeof(_message));
}

void			PaquetChat::createPaquet()
{
  size_t	ptr = 0;

  writeData<uint8_t>(ptr, &_id);
  writeData<uint8_t>(ptr, &_pID);
  writeData<char>(ptr, _message, sizeof(_message));
}

std::ostream	&operator<<(std::ostream &os, PaquetChat &p)
{
  p.parsePaquet();
  os << "PaquetChat = { message : "
     << p.getMessage()
     << ", PlayerID : "
     << static_cast<int>(p.getID())
     << " };";
  return (os);
}
