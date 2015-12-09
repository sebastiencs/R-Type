//
// Debug.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 10 22:48:47 2015 chapui_s
// Last update Tue Nov 10 22:48:47 2015 chapui_s
//

#ifndef DEBUG_H_
# define DEBUG_H_

# ifdef DEBUG
#  include <iostream>
#  if DEBUG >= 2
#   define DEBUG_MSG(x)	do { std::cerr << __PRETTY_FUNCTION__ << " : " << x << std::endl; } while (0)
#  else
#   define DEBUG_MSG(x)	do { std::cerr <<  x << std::endl; } while (0)
#  endif
# else
#  define DEBUG_MSG(x)
# endif // !DEBUG

# ifdef __unix__

#  define UNUSED __attribute__((__unused__))

# elif defined(_WIN32)

#  define UNUSED

# endif

#endif /* !DEBUG_H_ */
