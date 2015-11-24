//
// Party.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 10 22:42:25 2015 chapui_s
// Last update Tue Nov 10 22:42:25 2015 chapui_s
//

#ifndef PARTY_H_
# define PARTY_H_

# include <list>
# include <memory>
# include "Semaphore.hh"
# include "Thread.hh"
# include "Debug.hh"
# include "Player.hh"

typedef std::list<Player *>	listPlayers;

class		Party
{
  std::unique_ptr<Semaphore>	_sem;
  std::unique_ptr<Thread>	_thread;
  std::string	_name;
  listPlayers	_players;

public:
  Party();
  Party(const std::string &);
  virtual ~Party();

  void			run();
  void			stop();
  const listPlayers	&getPlayers() const;
  uint8_t		getNb() const;
  const std::string	&getName() const;
  bool			addPlayer(Player *);
  void			deletePlayer(socket_t);
};

#endif /* !PARTY_H_ */
