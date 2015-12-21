//
// Paquet.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Fri Nov 13 20:54:06 2015 chapui_s
// Last update Fri Nov 13 20:54:06 2015 chapui_s
//

#ifndef PAQUET_H_
# define PAQUET_H_

# include <iostream>
# include <string>

# include "Buffer.hh"

class		Paquet
{
protected:

  uint8_t	*_data;
  size_t	_size;

  void		setSize(size_t size) {
    _size = size;
  }

  void		changeSize(size_t size) {
  uint8_t	*tmp = new uint8_t[size];

  std::copy(_data, _data + _size, tmp);
  delete[] _data;
  _data = tmp;
  _size = size;
  }

public:

  enum {
    PAQUET_SIZE		= 0x01
  };

  enum {
    FIRST		= 0x00,
    REQUEST_PARTIES	= 0x01,
    LIST_PARTIES	= 0x02,
    JOIN_PARTY		= 0x03,
    CREATE_PARTY	= 0x04,
    REQUEST_PLAYERS	= 0x05,
    LIST_PLAYERS	= 0x06,
    COORD_PLAYER	= 0x07,
    PLAYER_SHOT		= 0x08,
    OBSTACLE		= 0x09,
    READY		= 0x0A,
    LAUNCH		= 0x0B,
    LEAVE		= 0x0C,
    FIRST_UDP		= 0x0D,
    ENEMY		= 0x0E,
    BONUS_MALUS		= 0x0F,
    LIFE	        = 0x10,
    DEATH	        = 0x11,
    RESPONSE		= 0xFF
  };

  enum { TCP, UDP };

  int	getType() const {
    if (_data && _size > 0) {

      uint8_t id = _data[0];

      if (id == COORD_PLAYER || id == PLAYER_SHOT || id == OBSTACLE || id == LEAVE || id == ENEMY || id == LIFE) {
	return (UDP);
      }
      else {
	return (TCP);
      }
    }
    return (TCP);
  }


  Paquet() : _data(nullptr) {
    _data = new uint8_t[Paquet::PAQUET_SIZE];
    _size = Paquet::PAQUET_SIZE;
  }

  Paquet(const Paquet &paquet) : _data(nullptr) {
    _data = new uint8_t[paquet.getSize()];
    _size = paquet.getSize();

    const uint8_t	*data = paquet.getData();
    size_t		ptr = 0;
    writeData(ptr, reinterpret_cast<const uint8_t *>(data), _size);
  }

  Paquet(const Buffer &buffer) : _data(nullptr) {
    _data = new uint8_t[buffer.size()];
    _size = buffer.size();

    const uint8_t	*data = buffer.get();
    size_t		ptr = 0;
    writeData(ptr, reinterpret_cast<const uint8_t *>(data), _size);
  }

  template<typename T>
  Paquet(const T *data, size_t len) : _data(nullptr) {
    size_t ptr = 0;

    _data = new uint8_t[len];
    _size = len;

    writeData(ptr, reinterpret_cast<const uint8_t *>(data), len);
  }

  virtual ~Paquet() {
    delete[] _data;
  }

  virtual void	createPaquet() {};

  size_t	getSize() const {
    return (_size);
  }

  const uint8_t	*getData() const {
    return (_data);
  }

  template<typename T>
  void		writeData(size_t &ptr, const T *new_data, size_t len = 0) {

    if (!len && !std::is_same<T, char>::value) {
      len = sizeof(T);
    }
    if (ptr + len >= _size) {
      changeSize(ptr + len);
    }

    const uint8_t *src = reinterpret_cast<const uint8_t *>(new_data);

    std::copy(src, src + len, _data + ptr);
    ptr += len;
  }

  template<typename T>
  T		readData(size_t &ptr, T *buffer = 0, size_t len = 0) const {
    T		value = 0;
    uint8_t	*byte;

    if (!len && !std::is_same<T, char>::value) {
      len = sizeof(T);
    }

    byte = reinterpret_cast<uint8_t *>((buffer) ? (buffer) : (&value));

    std::copy(_data + ptr, _data + ptr + len, byte);
    ptr += len;
    return (value);
  }

  Paquet	&operator=(const Paquet &paquet) {

    if (this == &paquet) {
      return (*this);
    }

    if (_size != paquet.getSize()) {
      delete[] _data;
      _data = new uint8_t[paquet.getSize()];
      _size = paquet.getSize();
    }

    const uint8_t	*data = paquet.getData();
    std::copy(data, data + _size, _data);
    return (*this);
  }
};

template<typename T>
T		&operator<<(T &s, Paquet &p)
{
  Buffer	buf;

  p.createPaquet();
  buf.set(p.getData(), p.getSize());
  s.write(buf);
  return (s);
}

template<typename T>
T		*operator<<(T *s, Paquet &p)
{
  Buffer	buf;

  p.createPaquet();
  buf.set(p.getData(), p.getSize());
  s->write(buf);
  return (s);
}

#endif /* !PAQUET_H_ */
