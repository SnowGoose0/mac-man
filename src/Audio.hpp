#pragma once

#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>

#include "Common.hpp"

#define DEFAULT_VOLUME 			15

#define AUDIO_MENU				0
#define AUDIO_GAME_START		1
#define AUDIO_GAME_OVER			2
#define AUDIO_EAT_PALLET		3
#define AUDIO_EAT_GHOST			4
#define AUDIO_POWER_UP			5
#define AUDIO_DEATH				6
#define AUDIO_FULL				7
#define AUDIO_1000_SCORE	   	8

#define AUDIO_MENU_PATH			"./audio/menu.ogg"
#define AUDIO_GAME_START_PATH   "./audio/genesis.ogg"
#define AUDIO_GAME_OVER_PATH    "./audio/termination.ogg"
#define AUDIO_EAT_PALLET_PATH   "./audio/consume.ogg"
#define AUDIO_EAT_GHOST_PATH    "./audio/demolish.ogg"
#define AUDIO_POWER_UP_PATH   	"./audio/power.ogg"
#define AUDIO_DEATH_PATH		"./audio/disintegration.ogg"
#define AUDIO_FULL_PATH		  	"./audio/full.ogg"
#define AUDIO_1000_SCORE_PATH	"./audio/1000.ogg"

class AudioManager {
  
public:
  AudioManager();
  ~AudioManager();
  
  void play(int id);
  void playLoop(int id);
  void stop(int id);
  
private:
  std::vector<std::string> _paths;
  std::vector<sf::SoundBuffer*> _buffers;
  std::vector<sf::Sound*> _audios;  
};
