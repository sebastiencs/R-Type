//
// Tools.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Dec  2 12:30:45 2015 chapui_s
// Last update Wed Dec  2 12:30:45 2015 chapui_s
//

#include "Tools.hh"


int		Tools::random(int min, int max)
{
  static int	done = 0;

  if (!done) {
    std::srand(static_cast<unsigned int>(std::time(0)));
  }

  max += 1;
  int num = std::rand() % (max - min) + min;
  return (num);
};

const std::string	&getUser()
{
#ifdef __unix__

  static std::string	namestr;
  char *user = getlogin();

  namestr = (user) ? (user) : ("Unknown");

  return (namestr);

#elif defined(_WIN32)



#endif
}
