#pragma once
#include "SFML/Audio.hpp"

namespace Sound
{
	enum class SoundType
	{
		BUTTON_CLICK,
	};

	class SoundService
	{
	  private:
		// TODO: Change back to 30 later
		const int background_music_volume = 0;

		sf::Music background_music;
		sf::Sound sound_effect;
		sf::SoundBuffer buffer_button_click;

		void loadBackgroundMusicFromFile();
		void loadSoundFromFile();

	  public:
		SoundService();

		void initialize();

		void playSound(SoundType soundType);
		void playBackgroundMusic();
	};
} // namespace Sound