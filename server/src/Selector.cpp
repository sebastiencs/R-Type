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

  _func[Paquet::FIRST]		 = [this](auto &buf, auto &addr) { this->call<PaquetFirst>		(buf, addr); };
  _func[Paquet::CREATE_PARTY]	 = [this](auto &buf, auto &addr) { this->call<PaquetCreateParty>	(buf, addr); };
  _func[Paquet::JOIN_PARTY]	 = [this](auto &buf, auto &addr) { this->call<PaquetJoinParty>		(buf, addr); };
  _func[Paquet::READY]		 = [this](auto &buf, auto &addr) { this->call<PaquetReady>		(buf, addr); };
  _func[Paquet::REQUEST_PARTIES] = [this](auto &buf, auto &addr) { this->call<PaquetRequestParties>	(buf, addr); };
  _func[Paquet::REQUEST_PLAYERS] = [this](auto &buf, auto &addr) { this->call<PaquetRequestPlayers>	(buf, addr); };
  _func[Paquet::FIRST_UDP] 	 = [this](auto &buf, auto &addr) { this->call<PaquetFirstUDP>		(buf, addr); };
  _func[Paquet::LEAVE]		 = [this](auto &buf, auto &)     { this->call<PaquetLeave>		(buf); };
  _func[Paquet::OBSTACLE] 	 = [this](auto &buf, auto &)     { this->call<PaquetObstacle>		(buf); };
  _func[Paquet::COORD_PLAYER]	 = [this](auto &buf, auto &)     { this->call<PaquetPlayerCoord>	(buf); };
  _func[Paquet::PLAYER_SHOT] 	 = [this](auto &buf, auto &)     { this->call<PaquetPlayerShot>		(buf); };
  _func[Paquet::RESPONSE] 	 = [this](auto &buf, auto &)     { this->call<PaquetResponse>		(buf); };
  _func[Paquet::RENAME] 	 = [this](auto &buf, auto &)     { this->call<PaquetRename>		(buf); };
  _func[Paquet::CHAT]	 	 = [this](auto &buf, auto &)     { this->call<PaquetChat>		(buf); };
}

Selector::~Selector()
{
}

template <typename PaquetType, typename... T>
inline void	Selector::call(const Buffer &buf, T... addr) {
  if (!_manager.expired()) {
    (_mPtr->*resolver<PaquetType>{}(&Manager::handlePaquet))(std::make_shared<PaquetType>(buf), addr...);
  }
}

int		Selector::execFunc(const Buffer &buf, const Addr &addr)
{
  const Data	*data = buf.get();

  if (!data || buf.size() <= 0) {
    std::cerr << "Wrong paquet size" << std::endl;
    return (-1);
  }

  _func[data[0]](buf, addr);

  return (0);
}




// template<class PaquetType, typename... Addr>
// auto Selector::resolver(void (Manager::*func)(std::shared_ptr<PaquetType>, Addr...)) -> decltype(func) {
//   return func;
// }


// #ifndef __GNUC__

// template <typename PaquetType, typename... T>
// inline void	Selector::call(const Buffer &buf, T... addr) {
//   if (!_manager.expired()) {
//     (_mPtr->*resolver<PaquetType>(&Manager::handlePaquet))(std::make_shared<PaquetType>(buf), addr...);
//   }
// }

// #endif // !__GNUC__


// #ifdef __GNUC__ // gcc is shit. seb
// template<class PaquetType> auto Selector::resolver(void (Manager::*func)(std::shared_ptr<PaquetType>)) -> decltype(func) { return func; } // Overload resolver with 1 arg
// template <typename PaquetType, typename... T> inline void Selector::call(const Buffer &buf, T... addr) //  call() with 2 args. Need to give <PaquetType, const Addr &>
// { if (!_manager.expired()) (_mPtr->*resolver<PaquetType, const Addr &>(&Manager::handlePaquet))(std::make_shared<PaquetType>(buf), addr...); }
// template <typename PaquetType> inline void Selector::call(const Buffer &buf) // call() with 1 arg. Give only <PaquetType>
// { if (!_manager.expired()) (_mPtr->*resolver<PaquetType>(&Manager::handlePaquet))(std::make_shared<PaquetType>(buf)); }
// #endif // !__GNUC__
