//
// Buffer.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Mon Nov 16 22:49:03 2015 chapui_s
// Last update Mon Nov 16 22:49:03 2015 chapui_s
//

#ifndef BUFFER_H_
# define BUFFER_H_

# include <memory>
# include <iostream>
# include "Debug.hh"

typedef std::unique_ptr<uint8_t[]>	buffer_t;
typedef uint8_t				Data;
typedef size_t				Size;

class		Buffer
{
private:

  enum { DEFAULT_SIZE = 0x200 };

  buffer_t	_buffer;
  Size		_size;
  size_t	_ptr;

public:
  Buffer();
  virtual ~Buffer();

  Data		*get() const;
  Size		size() const;
  void		setSize(Size size);
  void		reset();

  const Data	&operator[](Size id) const;
  const Buffer	&operator=(const Buffer &);
  const Buffer	&operator=(const Buffer *);

  template <typename T>
  Buffer(const T *ptr, Size len) {

    const Data	*data = reinterpret_cast<const Data *>(ptr);

    _buffer.reset(new Data[len]);
    std::copy(data, data + len, _buffer.get());
    _size = len;
    _ptr = len;
    DEBUG_MSG("Buffer created");
  }

  template <typename T>
  void		set(const T *ptr, Size len) {

    const Data	*data = reinterpret_cast<const Data *>(ptr);

    _buffer.reset(new Data[len]);
    std::copy(data, data + len, _buffer.get());
    _size = len;
    _ptr = len;
  }

  template <typename T>
  void		append(const T *ptr, Size len) {

    const Data	*data = reinterpret_cast<const Data *>(ptr);

    if (_ptr + len < _size) {

      std::copy(data, data + len, _buffer.get() + _ptr);
      _ptr += len;

    }
    else {

      Data *tmp = new Data[_size + len];

      std::copy(_buffer.get(), _buffer.get() + _size, tmp);
      std::copy(data, data + len, tmp + _size);

      _buffer.reset(new Data[_size + len]);

      std::copy(tmp, tmp + _size + len, _buffer.get());
      _ptr += len;

      delete[] tmp;

    }
  }
};

std::ostream	&operator<<(std::ostream &, const Buffer &);

#endif /* !BUFFER_H_ */
