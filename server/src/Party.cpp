//
// Party.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 10 22:44:37 2015 chapui_s
// Last update Tue Nov 10 22:44:37 2015 chapui_s
//

#include "Party.hh"

#ifdef __unix__
# include <unistd.h>
#endif

Party::Party()
  : _sem(new Semaphore()),
    _thread(new Thread()),
    _name("Unknwon")
{
  DEBUG_MSG("Party created");
  _thread->run([this](void *) -> void * { run(); return (0); }, 0);
}

Party::Party(const std::string &name)
  : _sem(new Semaphore()),
    _thread(new Thread()),
    _name(name)
{
  DEBUG_MSG("Party created");
  _thread->run([this](void *) -> void * { run(); return (0); }, 0);
}

Party::~Party()
{
  DEBUG_MSG("Party deleted");
}

void			Party::run()
{
  for (;;) {
    std::cerr << "A party is running" << std::endl;

#ifdef __unix__
    sleep(2);
#elif defined(_WIN32)
    Sleep(2);
#endif
  }
}

void			Party::stop()
{
  _thread->close();
}

const listPlayers	&Party::getPlayers() const
{
  return (_players);
}

uint8_t			Party::getNb() const
{
  return (static_cast<uint8_t>(_players.size()));
}

const std::string	&Party::getName() const
{
  return (_name);
}

bool			Party::addPlayer(Player *player)
{
  if (_players.size() < 4) {
    _players.push_back(player);
    return (true);
  }
  else {
    return (false);
  }
}

void			Party::deletePlayer(socket_t socket)
{
  auto p = std::find_if(_players.begin(), _players.end(), [&socket] (Player *p) { return (p->socket() == socket); });

  if (p != _players.end()) {
    delete *p;
    _players.erase(p);
    DEBUG_MSG("Player deleted from party");
  }
}
