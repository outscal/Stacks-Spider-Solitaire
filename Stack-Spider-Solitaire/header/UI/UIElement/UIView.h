#pragma once
#include <SFML/Graphics.hpp>

namespace UIElement
{
	enum class UIState
	{
		VISIBLE,
		HIDDEN,
	};

	class UIView
	{
	  protected:
		sf::RenderWindow* game_window;
		UIState ui_state;

	  public:
		UIView();
		virtual ~UIView();

		virtual void initialize() = 0;
		virtual void update() = 0;
		virtual void render() = 0;

		virtual void show() = 0;
		virtual void hide() = 0;
	};
} // namespace UIElement