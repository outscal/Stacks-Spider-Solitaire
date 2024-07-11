#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace Event
{
	enum class ButtonState
	{
		PRESSED,
		HELD,
		RELEASED,
	};

	class EventService
	{
	private:
		sf::Event game_event;
		sf::RenderWindow* game_window;

		ButtonState left_mouse_button_state;
		ButtonState right_mouse_button_state;
		ButtonState Z_button_state;
		ButtonState Ctrl_button_state;

		bool isGameWindowOpen();
		bool gameWindowWasClosed();
		bool hasQuitGame();
		bool isKeyboardEvent();
		void updateButtonsState(ButtonState& button_state);

		void updateKeyboardButtonsState(ButtonState& current_button_state, sf::Keyboard::Key keyboard_button);

	public:
		EventService();
		~EventService();

		void initialize();
		void update();
		void processEvents();

		bool pressedEscapeKey();
		bool pressedLeftMouseButton();
		bool pressedRightMouseButton();

		void setLeftMouseButtonState(ButtonState button_state);
		bool pressedZKey();
		bool pressedCtrlKey();
		bool isCtrlZPressed();
		

	};
}