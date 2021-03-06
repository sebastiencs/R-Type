
#ifndef WSA_HH_
# define WSA_HH_

# include <iostream>
# include "SocketsWin.hh"

namespace WSA
{
  static WSADATA _WSAData;

  bool    init() {
    bool  ret = false;

    if (WSAStartup(MAKEWORD(2, 0), &_WSAData)) {
      std::cerr << "WSAStartup() failed" << std::endl;
      ret = true;
    }
    return (ret);
  }

  void    clean() {
    WSACleanup();
  }
}

#endif // !WSA_HH_
