//
// SystemFile.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Dec 27 02:29:01 2015 chapui_s
// Last update Sun Dec 27 02:29:01 2015 chapui_s
//

#ifndef SYSTEMFILE_H_
# define SYSTEMFILE_H_

# ifdef __unix__
#  include "SystemFileUnix.hh"
# elif defined(_WIN32)
#  include "SystemFileWin.hh"
# else
#  error "Platform Unknown"
# endif

#endif /* !SYSTEMFILE_H_ */
