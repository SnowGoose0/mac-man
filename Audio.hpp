#pragma once

#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>

#include "Common.hpp"

#define DEFAULT_VOLUME 			15

#define AUDIO_GAME_START		0
#define AUDIO_GAME_OVER			1
#define AUDIO_EAT_PALLET		2
#define AUDIO_EAT_GHOST			3
#define AUDIO_POWER_UP			4
#define AUDIO_DEATH				5
#define AUDIO_FULL				6

#define AUDIO_GAME_START_PATH   "./audio/genesis.ogg"
#define AUDIO_GAME_OVER_PATH    "./audio/termination.ogg"
#define AUDIO_EAT_PALLET_PATH   "./audio/consume.ogg"
#define AUDIO_EAT_GHOST_PATH    "./audio/demolish.ogg"
#define AUDIO_POWER_UP_PATH   	"./audio/power.ogg"
#define AUDIO_DEATH_PATH		"./audio/disintegration.ogg"
#define AUDIO_FULL_PATH		  	"./audio/full.ogg"

class AudioManager {
  
public:
  AudioManager();
  ~AudioManager();
  
  void play(int id);
  
private:
  std::vector<std::string> _paths;
  std::vector<sf::SoundBuffer*> _buffers;
  std::vector<sf::Sound*> _audios;  
};
