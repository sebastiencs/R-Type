//
// Semaphore.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 18 22:23:47 2015 chapui_s
// Last update Wed Nov 18 22:23:47 2015 chapui_s
//

#ifndef SEMAPHORE_H_
# define SEMAPHORE_H_

# ifdef __unix__

#  include "SemaphoreUnix.hh"
typedef SemaphoreUnix Semaphore;

# elif defined(_WIN32)

#  include "SemaphoreWin.hh"
typedef SemaphoreWin Semaphore;

# endif

#endif /* !SEMAPHORE_H_ */
