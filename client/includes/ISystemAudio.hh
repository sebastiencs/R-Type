//
// ISystemAudio.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Dec  2 08:42:11 2015 chapui_s
// Last update Wed Dec  2 08:42:11 2015 chapui_s
//

#ifndef ISYSTEMAUDIO_H_
# define ISYSTEMAUDIO_H_

# include <iostream>

typedef int	SoundID;
typedef int	MusicID;

class		ISystemAudio
{
public:
  virtual ~ISystemAudio() {};

  virtual void	loadMusic(const std::string &file, const int id) = 0;
  virtual void	loadSound(const std::string &file, const int id) = 0;

  virtual void	playMusic(const int id) = 0;
  virtual void	playSound(const int id) = 0;

  virtual void	playMusicRandom() = 0;

  virtual void	stopMusic() = 0;
  virtual void	stopSound() = 0;

	enum {
		SIMPLE_SHOT = 1,
		JOIN,
		DEATH,
		BONUS
  };

};


#endif /* !ISYSTEMAUDIO_H_ */
