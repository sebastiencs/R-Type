//
// Signals.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov 29 18:50:14 2015 chapui_s
// Last update Sun Nov 29 18:50:14 2015 chapui_s
//

#ifndef SIGNALS_H_
# define SIGNALS_H_

# ifdef __unix__

#  include "SignalUnix.hh"
typedef SignalUnix	Signal;

# elif defined(_WIN32)

#  include "SignalWin.hh"
typedef SignalWin	Signal;

# endif

#endif /* !SIGNALS_H_ */
