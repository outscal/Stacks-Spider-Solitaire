#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace Global
{
	class Config
	{
	public:
		static const sf::String outscal_logo_texture_path;
		static const sf::String background_texture_path;
		static const sf::String level_background_texture_path;

		static const sf::String play_button_texture_path;
		static const sf::String instructions_button_texture_path;
		static const sf::String quit_button_texture_path;

		static const sf::String bubble_bobble_font_path;
		static const sf::String DS_DIGIB_font_path;

		static const sf::String background_music_path;
		static const sf::String button_click_sound_path;
	};
}