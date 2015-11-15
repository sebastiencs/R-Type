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

# include "Socket.hh"

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
    PAQUET_SIZE        = 0x01
  };

  enum {
    FIRST              = 0x00,
    REQUEST_PARTIES    = 0x01,
    LIST_PARTIES       = 0x02,
    JOIN_PARTY         = 0x03,
    CREATE_PARTY       = 0x04,
    REQUEST_PLAYERS    = 0x05,
    LIST_PLAYERS       = 0x06,
		COORD_PLAYER       = 0x07,
    RESPONSE           = 0xFF
  };


  Paquet() {
    _data = new uint8_t[Paquet::PAQUET_SIZE];
    _size = Paquet::PAQUET_SIZE;
  }

  virtual ~Paquet() {
    delete[] _data;
  }

  virtual void	createPaquet() = 0;

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

    size_t i;
    for (i = 0; i < len; i += 1) {
      _data[ptr + i] = reinterpret_cast<const uint8_t *>(new_data)[i];
    }
    ptr += i;
  }

  template<typename T>
  T		readData(size_t &ptr, T *buffer = 0, size_t len = 0) const {
    T		value = 0;
    uint8_t	*byte;

    if (!len && !std::is_same<T, char>::value) {
      len = sizeof(T);
    }

    byte = reinterpret_cast<uint8_t *>((buffer) ? (buffer) : (&value));

    if (ptr + len <= _size) {
      for (size_t i = 0; i < len; i += 1) {
	byte[i] = _data[ptr];
	ptr += 1;
      }
    }
    return (value);
  }
};

template<typename T>
T		&operator<<(T &s, Paquet &p)
{
  p.createPaquet();
  s.write(reinterpret_cast<const char *>(p.getData()), p.getSize());
  return (s);
}

template<typename T>
T		*operator<<(T *s, Paquet &p)
{
  p.createPaquet();
  s->write(reinterpret_cast<const char *>(p.getData()), p.getSize());
  return (s);
}

#endif /* !PAQUET_H_ */
