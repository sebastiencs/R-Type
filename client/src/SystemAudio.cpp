//
// SystemAudio.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Dec  2 08:49:14 2015 chapui_s
// Last update Wed Dec  2 08:49:14 2015 chapui_s
//

#include "SystemAudio.hh"
#include "Tools.hh"
#include "Debug.hh"

SystemAudio::SystemAudio()
  : _currentMusic(nullptr),
    _currentSound(nullptr)
{
  DEBUG_MSG("SystemAudio created");
}

SystemAudio::~SystemAudio()
{
  DEBUG_MSG("SystemAudio deleted");
  _musics.clear();
  _sounds.clear();
}

void	SystemAudio::loadMusic(const std::string &file, int id)
{

  if (Tools::findIt(_musics, [&id] (const UMusic &m) { return (m->id == id); }) != _musics.end()) {
    DEBUG_MSG("A music with same id already exist");
    return ;
  }

  sf::Music *sfmusic = new sf::Music();

  if (sfmusic->openFromFile(RS_PATH + file)) {

    Music	*music = new Music;

    music->id = id;
    music->music.reset(sfmusic);

    _musics.push_back(UMusic(music));

  }
  else {
    delete sfmusic;
    throw ErrorLoadingFile(file);
  }
}

void	SystemAudio::loadSound(const std::string &file, int id)
{

  if (Tools::findIt(_sounds, [&id] (const USound &m) { return (m->id == id); }) != _sounds.end()) {
    DEBUG_MSG("A music with same id already exist");
    return ;
  }

  sf::SoundBuffer *buffer = new sf::SoundBuffer;

  if (buffer->loadFromFile(RS_PATH + file)) {

    sf::Sound *sfsound = new sf::Sound();

    sfsound->setBuffer(*buffer);

    Sound *sound = new Sound();

    sound->id = id;
    sound->buffer.reset(buffer);
    sound->sound.reset(sfsound);

    _sounds.push_back(USound(sound));

  }
  else {
    delete buffer;
    throw ErrorLoadingFile(file);
  }
}

void	SystemAudio::playMusic(int id)
{
  auto it = Tools::findIt(_musics, [&id] (const UMusic &m) { return (m->id == id); });

  if (it != _musics.end()) {
    (*it)->music->play();
    _currentMusic = (*it)->music.get();
  }
  else {
    DEBUG_MSG("Music not found");
  }
}

void	SystemAudio::playSound(int id)
{
  auto it = Tools::findIt(_sounds, [&id] (const USound &s) { return (s->id == id); });

  if (it != _sounds.end()) {
    (*it)->sound->play();
    _currentSound = (*it)->sound.get();
  }
  else {
    DEBUG_MSG("Music not found");
  }
}

void	SystemAudio::playMusicRandom()
{
  if (_musics.empty()) {
    return ;
  }

  stopMusic();

  int	i = 0;
  int	n = Tools::random(0, _musics.size() - 1);

  for (auto &music : _musics) {
    if (i == n) {
      music->music->play();
      _currentMusic = music->music.get();
      break ;
    }
    i += 1;
  }
}

void	SystemAudio::stopMusic()
{
  if (_currentMusic) {
    _currentMusic->stop();
  }
}

void	SystemAudio::stopSound()
{
  if (_currentSound) {
    _currentSound->stop();
  }
}
