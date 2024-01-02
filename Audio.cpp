#include "Audio.hpp"

AudioManager::AudioManager() {
  _paths = {
	AUDIO_GAME_START_PATH,
	AUDIO_GAME_OVER_PATH,
	AUDIO_EAT_PALLET_PATH,
	AUDIO_EAT_GHOST_PATH,
	AUDIO_POWER_UP_PATH,
	AUDIO_DEATH_PATH,
	AUDIO_FULL_PATH
  };

  for (auto it = _paths.begin(); it != _paths.end(); it++) {
	sf::SoundBuffer* buffer = new sf::SoundBuffer();
	sf::Sound* sound = new sf::Sound();

	if (!buffer->loadFromFile(*it)) {
	  std::cout << "Error: cannot load audio files" << std::endl;
	  exit(EXIT_FAILURE);
	}
	
	sound->setBuffer(*buffer);
	sound->setVolume(DEFAULT_VOLUME);

	_buffers.push_back(buffer);
	_audios.push_back(sound);
  }
}

AudioManager::~AudioManager() {
  for (int i = 0; i < _buffers.size(); i++) {
	delete _buffers[i];
	delete _audios[i];
  }
}

void AudioManager::play(int id) {
  _audios[id]->play();
}
