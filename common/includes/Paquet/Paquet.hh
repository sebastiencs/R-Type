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
    RESPONSE           = 0xFF
  };


  Paquet() {
    _data = new uint8_t[Paquet::PAQUET_SIZE];
    _size = Paquet::PAQUET_SIZE;
  }

  virtual ~Paquet() {
    delete[] _data;
  }

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

    std::copy(new_data, new_data + len, _data + ptr);
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

    if (ptr + len <= _size) {
      std::copy(_data + ptr, _data + ptr + len, byte);
      ptr += len;
    }
    return (value);
  }
};

// std::ostream	&operator<<(std::ostream &os, const Paquet &p)
// {
//   const uint8_t	*data;

//   data = p.getData();
//   os << "Paquet = { ";
//   os << std::hex << std::uppercase;
//   for (size_t i = 0; i < p.getSize(); i += 1) {
//     os << (int)((unsigned char)data[i]) << " ";
//   }
//   os << std::dec << "}; " << std::endl;
//   return (os);
// }

#endif /* !PAQUET_H_ */
