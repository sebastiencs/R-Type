//
// Buffer.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Mon Nov 16 22:56:00 2015 chapui_s
// Last update Mon Nov 16 22:56:00 2015 chapui_s
//

#include "Buffer.hh"

Buffer::Buffer()
  : _buffer(new Data[Buffer::DEFAULT_SIZE]),
    _size(Buffer::DEFAULT_SIZE)
{
  DEBUG_MSG("Buffer created");
}

Buffer::Buffer(const Data *data, Size len)
{
  _buffer.reset(new Data[len]);
  std::copy(data, data + len, _buffer.get());
  _size = len;
  DEBUG_MSG("Buffer created");
}

Buffer::~Buffer()
{
  DEBUG_MSG("Buffer deleted");
}

void		Buffer::set(const Data *data, Size len)
{
  _buffer.reset(new Data[len]);
  std::copy(data, data + len, _buffer.get());
  _size = len;
}

Data		*Buffer::get() const
{
  return (_buffer.get());
}

Size		Buffer::size() const
{
  return (_size);
}

void		Buffer::setSize(Size size)
{
  if (size <= _size) {
    _size = size;
  }
  else {
    Data *tmp = new Data[size];

    std::copy(_buffer.get(), _buffer.get() + size, tmp);
    _buffer.reset(new Data[size]);
    std::copy(tmp, tmp + size, _buffer.get());
    _size = size;
  }
}

void		Buffer::reset()
{
  _buffer.reset(new Data[Buffer::DEFAULT_SIZE]);
  _size = Buffer::DEFAULT_SIZE;
}

const Data	&Buffer::operator[](Size id) const
{
  if (id <= _size) {
    return (_buffer.get()[id]);
  }
  else {
    throw std::runtime_error("Wrong access on buffer");
  }
}

const Buffer	&Buffer::operator=(const Buffer &buf)
{
  set(buf.get(), buf.size());
  return (*this);
}

std::ostream	&operator<<(std::ostream &os, const Buffer &b)
{
  unsigned char	*data;

  data = b.get();
  os << "Buffer = { ";
  os << std::hex << std::uppercase;
  for (size_t i = 0; i < b.size(); i += 1) {
    os << (int)((unsigned char)data[i]) << " ";
  }
  os << std::dec << "}; ";
  return (os);
}
