//
// PaquetTCP.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Dec  2 01:14:32 2015 chapui_s
// Last update Wed Dec  2 01:14:32 2015 chapui_s
//

#include "PaquetTCP.hh"

PaquetTCP::PaquetTCP(SocketTCP::CONNECTION_TYPE type)
  : SocketTCP(type),
    _buffer(new Buffer()),
    _bufferTMP(new Buffer()),
    _start(true),
    _sizeCurrent(0)
{
  initSize();
}

PaquetTCP::PaquetTCP(SocketTCP::CONNECTION_TYPE type, socket_t sock)
  : SocketTCP(type, sock),
    _buffer(new Buffer()),
    _bufferTMP(new Buffer()),
    _start(true),
    _sizeCurrent(0)
{
  initSize();
}

PaquetTCP::~PaquetTCP()
{
}

void	PaquetTCP::initSize()
{
  // Define Paquets size
  _pSize[Paquet::FIRST]			= 0x14;
  _pSize[Paquet::REQUEST_PARTIES]	= 0x01;
  _pSize[Paquet::LIST_PARTIES]		= UNKNOWN_SIZE;
  _pSize[Paquet::JOIN_PARTY]		= 0x11;
  _pSize[Paquet::CREATE_PARTY]		= 0x11;
  _pSize[Paquet::REQUEST_PLAYERS]	= 0x01;
  _pSize[Paquet::LIST_PLAYERS]		= UNKNOWN_SIZE;
  _pSize[Paquet::COORD_PLAYER]		= 0x04;
  _pSize[Paquet::PLAYER_SHOT]		= 0x05;
  _pSize[Paquet::OBSTACLE]		= 0x04;
  _pSize[Paquet::READY]			= 0x02;
  _pSize[Paquet::LAUNCH]		= 0x01;
  _pSize[Paquet::LEAVE]			= 0x02;
  _pSize[Paquet::RESPONSE]		= 0x06;
}

ssize_t		PaquetTCP::read(Buffer &buf)
{
  ssize_t	n = 0;

  if (_start == true) {

    uint8_t	id;
# ifdef __unix__
	n = ::read(_socket, &id, sizeof(id));
# elif defined(_WIN32)
	n = recv(_socket, &id, sizeof(id), 0);
#endif
	if (n > 0) {
      if (_pSize.count(id)) {
	_idPaquet = id;
	_sizeCurrent = 1;
	_sizePaquet = _pSize[id];
	_start = false;
	_buffer->append(&id, sizeof(id));
      }
      else {
	std::cerr << "Unknown paquet id: " << static_cast<int>(id) << std::endl;
	return (0);
      }
    }
    else {
      throw Disconnected();
    }
  }

  if (_sizePaquet == UNKNOWN_SIZE) {

    if (_idPaquet == Paquet::LIST_PARTIES) {

      uint16_t nb;
# ifdef __unix__
	  n = ::read(_socket, &nb, sizeof(nb));
# elif defined(_WIN32)
	  n = recv(_socket, &nb, sizeof(nb), 0);
#endif
	  if (n == 2) {
	_sizeCurrent += 2;
	_sizePaquet = 3 + nb * 17;
	_buffer->append(&nb, sizeof(nb));
	if (nb == 0) {
	  // Pas de parties: Fin de lecture du paquet
	  return (readDone(buf));
	}
      }
      else if (n == 1) {
	throw std::runtime_error("PaquetTCP: Unimplemented error");
	// TODO: Ca a chier dans la colle
      }
      else {
	throw Disconnected();
      }
    }
    else if (_idPaquet == Paquet::LIST_PLAYERS) {

      uint8_t	nb;
# ifdef __unix__
	  n = ::read(_socket, &nb, sizeof(nb));
# elif defined(_WIN32)
	  n = recv(_socket, &nb, sizeof(nb), 0);
#endif
      if (n == 1) {
	_sizeCurrent += 1;
	_sizePaquet = 2 + nb * 18;
	_buffer->append(&nb, sizeof(nb));
	if (nb == 0) {
	  // Pas de joueurs: Fin de lecture du paquet
	  return (readDone(buf));
	}
      }
      else {
	throw Disconnected();
      }
    }
  }

  if (_sizePaquet != UNKNOWN_SIZE) {

    uint16_t	left = _sizePaquet - _sizeCurrent;

    _bufferTMP->reset();

# ifdef __unix__
	n = ::read(_socket, _bufferTMP->get(), left);
# elif defined(_WIN32)
	n = recv(_socket, _bufferTMP->get(), left, 0);
#endif

    if (n > 0) {
      _sizeCurrent += n;
      _buffer->append(_bufferTMP->get(), n);
      if (_sizeCurrent == _sizePaquet) {
	// Fin de lecture du paquet
	return (readDone(buf));
      }
    }
    else {
      throw Disconnected();
    }
  }

  return (0);
}

ssize_t		PaquetTCP::readDone(Buffer &buf)
{
  ssize_t	size = _sizePaquet;

  buf = _buffer.get();
  buf.setSize(_sizePaquet);

  _buffer->reset();
  _start = true;
  _sizeCurrent = 0;
  _sizePaquet = 0;
  _idPaquet = 0;

  return (size);
}
