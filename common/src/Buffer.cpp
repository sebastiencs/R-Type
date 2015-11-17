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
  : _buffer(new Data[512]),
    _size(512)
{
  DEBUG_MSG("Buffer created");
}

Buffer::Buffer(Data *data, Size len)
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
    Data *tmp = new Data(size);

    std::copy(_buffer.get(), _buffer.get() + size, tmp);
    _buffer.reset(new Data[size]);
    std::copy(tmp, tmp + size, _buffer.get());
    _size = size;
  }
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
