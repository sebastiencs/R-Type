//
// Game.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Dec  8 23:13:48 2015 chapui_s
// Last update Tue Dec  8 23:13:48 2015 chapui_s
//

#ifndef GAME_H_
# define GAME_H_

# include <deque>
# include "DisplayUpdater.hh"

class PackageStorage;
class ISystemAudio;
class ListPlayers;

class		Game
{
private:

	PackageStorage	&_PS;
	ISystemAudio		&_audio;
	ListPlayers		&_LP;
	IMutex		*_mutex;
	std::deque<Image> &_speudo;
	std::deque<Image>	&_images;
	ITimer		*_timer;
	int			_width;
	int			_height;

public:
	Game(int width, int height, std::deque<Image> &images, IMutex *mutex, std::deque<Image> &speudo);
	virtual ~Game();

	void	run();
	void	handlingNetwork();
	void	updateGraphic();

	template<typename... Args>
	void drawImage(Args... args) {
		_mutex->lock();
		_images.emplace_back(args...);
		_mutex->unlock();
	};

	template<typename... Args>
	void drawText(Args... args) {
		_mutex->lock();
		_speudo.emplace_back(args...);
		_mutex->unlock();
	};

	template<class T>
	bool	remove_elem(T &elem) {
		DEBUG_MSG("Elem X: " << elem.x << "window: " << _width);
		if (elem.x > _width) {
			return true;
		}
		return false;
	};

};

#endif /* !GAME_H_ */