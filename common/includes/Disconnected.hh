//
// Disconnected.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Dec  2 04:24:56 2015 chapui_s
// Last update Wed Dec  2 04:24:56 2015 chapui_s
//

#ifndef DISCONNECTED_H_
# define DISCONNECTED_H_

# include <stdexcept>

class		Disconnected : public std::runtime_error
{
public:
  Disconnected()
    : std::runtime_error("Disconnected")
    {
    }

  Disconnected(const std::string &str)
    : std::runtime_error(str)
    {
    }

  virtual ~Disconnected() throw()
    {
    }
};

#endif /* !DISCONNECTED_H_ */
