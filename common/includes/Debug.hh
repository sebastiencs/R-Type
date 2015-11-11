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
#  define DEBUG_MSG(x)	do { std::cerr << x << std::endl; } while (0)
# else
#  define DEBUG_MSG(x)
# endif // !DEBUG

#endif /* !DEBUG_H_ */
