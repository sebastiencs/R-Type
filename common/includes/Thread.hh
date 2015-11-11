//
// Thread.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 11 00:48:19 2015 chapui_s
// Last update Wed Nov 11 00:48:19 2015 chapui_s
//

#ifndef THREAD_H_
# define THREAD_H_

# ifdef __unix__

#   include "ThreadUnix.hh"
typedef ThreadUnix Thread;

# elif defined(_WIN32)

#   include "ThreadWin.hh"
typedef ThreadWin Thread;

# else

#   error "Platform Unknown"

# endif

#endif /* !THREAD_H_ */
