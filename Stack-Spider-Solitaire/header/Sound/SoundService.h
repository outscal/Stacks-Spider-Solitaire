#pragma once
#include "SFML/Audio.hpp"

namespace Sound
{
	enum class SoundType
	{
		BUTTON_CLICK,
		LEVEL_COMPLETE,
	};

	class SoundService
	{
	private:
		const int background_music_volume = 30;

		sf::Music background_music;
		sf::Sound sound_effect;
		sf::SoundBuffer buffer_button_click;
		sf::SoundBuffer buffer_level_complete;

		void loadBackgroundMusicFromFile();
		void loadSoundFromFile();

	public:
		SoundService();

		void initialize();

		void playSound(SoundType soundType);
		void playBackgroundMusic();
	};
}