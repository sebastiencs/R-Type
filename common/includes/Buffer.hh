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

typedef std::unique_ptr<uint8_t>	buffer_t;
typedef uint8_t				Data;
typedef size_t				Size;

class		Buffer
{
private:

  buffer_t	_buffer;
  Size		_size;

public:
  Buffer();
  Buffer(Data *data, Size len);
  virtual ~Buffer();

  void		set(const Data *data, Size len);
  Data		*get() const;
  Size		size() const;
  void		setSize(Size size);

  const Data	&operator[](Size id) const;
  const Buffer	&operator=(const Buffer &);
};

#endif /* !BUFFER_H_ */
