//
// SystemAudio.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Dec  2 08:47:45 2015 chapui_s
// Last update Wed Dec  2 08:47:45 2015 chapui_s
//

#ifndef SYSTEMAUDIO_H_
# define SYSTEMAUDIO_H_

# include <SFML/Audio.hpp>
# include <memory>
# include <list>
# include "ISystemAudio.hh"

# define RS_PATH "ressources/"

typedef struct {
  int id;
  std::unique_ptr<sf::Music> music;
} Music;

typedef struct {
  int id;
  std::unique_ptr<sf::SoundBuffer> buffer;
  std::unique_ptr<sf::Sound> sound;
} Sound;

typedef std::unique_ptr<Music>	UMusic;
typedef std::unique_ptr<Sound>	USound;

class		SystemAudio : public ISystemAudio
{
private:
  std::list<UMusic>	_musics;
  std::list<USound>	_sounds;

  sf::Music		*_currentMusic;
  sf::Sound		*_currentSound;

public:
  SystemAudio();
  virtual ~SystemAudio();

  static SystemAudio &getInstance();

  virtual void	loadMusic(const std::string &file, int id);
  virtual void	loadSound(const std::string &file, int id);

  virtual void	playMusic(int id);
  virtual void	playSound(int id);

  virtual void	playMusicRandom();

  virtual void	stopMusic();
  virtual void	stopSound();

};

# include <stdexcept>

class		ErrorLoadingFile : public std::runtime_error
{
public:
  ErrorLoadingFile()
    : std::runtime_error("ErrorLoadingFile")
    {
    }

  ErrorLoadingFile(const std::string &str)
    : std::runtime_error("ErrorLoadingFile: " + str)
    {
    }

  virtual ~ErrorLoadingFile() throw()
    {
    }
};

#endif /* !SYSTEMAUDIO_H_ */
