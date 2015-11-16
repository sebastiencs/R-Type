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
{
  DEBUG_MSG("Buffer created");
}

Buffer::Buffer(Data *data, Size len)
{
  _buffer.reset(new uint8_t[len]);
  std::copy(data, data + len, _buffer.get());
  _size = len;
  DEBUG_MSG("Buffer created");
}

Buffer::~Buffer()
{
  DEBUG_MSG("Buffer deleted");
}

void		Buffer::set(Data *data, Size len)
{
  _buffer.reset(new uint8_t[len]);
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
