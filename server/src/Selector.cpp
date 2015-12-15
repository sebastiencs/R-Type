//
// Selector.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Nov 24 04:25:50 2015 chapui_s
// Last update Tue Nov 24 04:25:50 2015 chapui_s
//

#include "Selector.hh"
#include "Manager.hh"

Selector::Selector(const Manager_SharedPtr &&manager)
  : _manager(std::move(manager)),
    _mPtr(manager.get()),
    _func(0x100)
{
  std::fill(_func.begin(), _func.end(), [this] (auto &, auto &) -> void { std::cerr << "Unknown paquet" << std::endl; });

  _func[Paquet::FIRST]		 = [this](auto &buf, auto &addr) { call<PaquetFirst>		(buf, addr); };
  _func[Paquet::CREATE_PARTY]	 = [this](auto &buf, auto &addr) { call<PaquetCreateParty>	(buf, addr); };
  _func[Paquet::JOIN_PARTY]	 = [this](auto &buf, auto &addr) { call<PaquetJoinParty>	(buf, addr); };
  _func[Paquet::LEAVE]		 = [this](auto &buf, auto &addr) { call<PaquetLeave>		(buf, addr); };
  _func[Paquet::OBSTACLE] 	 = [this](auto &buf, auto &addr) { call<PaquetObstacle>		(buf, addr); };
  _func[Paquet::COORD_PLAYER]	 = [this](auto &buf, auto &addr) { call<PaquetPlayerCoord>	(buf, addr); };
  _func[Paquet::PLAYER_SHOT] 	 = [this](auto &buf, auto &addr) { call<PaquetPlayerCoord>	(buf, addr); };
  _func[Paquet::READY]		 = [this](auto &buf, auto &addr) { call<PaquetReady>		(buf, addr); };
  _func[Paquet::REQUEST_PARTIES] = [this](auto &buf, auto &addr) { call<PaquetRequestParties>	(buf, addr); };
  _func[Paquet::REQUEST_PLAYERS] = [this](auto &buf, auto &addr) { call<PaquetRequestPlayers>	(buf, addr); };
  _func[Paquet::RESPONSE] 	 = [this](auto &buf, auto &addr) { call<PaquetResponse>		(buf, addr); };
  _func[Paquet::FIRST_UDP] 	 = [this](auto &buf, auto &addr) { call<PaquetFirstUDP>		(buf, addr); };
}

Selector::~Selector()
{
}

template<class PaquetType>
auto Selector::resolver(void (Manager::*func)(typename std::add_pointer<PaquetType>::type, const Addr &)) -> decltype(func) {
  return func;
}

template <typename PaquetType>
inline void	Selector::call(const Buffer &buf, const Addr &addr)
{
  if (!_manager.expired()) {
    (_mPtr->*resolver<PaquetType>(&Manager::handlePaquet))(new PaquetType(buf), addr);
  }
}

int		Selector::execFunc(const Buffer &buf, const Addr &addr)
{
  Data		*data = buf.get();

  if (!data || buf.size() <= 0) {
    std::cerr << "Wrong paquet size" << std::endl;
    return (-1);
  }

  _func[data[0]](buf, addr);

  return (0);
}
