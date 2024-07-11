#include "../../header/Event/EventService.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Graphics/GraphicService.h"
#include <iostream>

namespace Event
{
    using namespace Global;
    using namespace Graphics;

    EventService::EventService() { game_window = nullptr; }

    EventService::~EventService() = default;

    void EventService::initialize()
    {
        game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();
    }

    void EventService::update()
    {
        updateButtonsState(left_mouse_button_state);
        updateButtonsState(right_mouse_button_state);
        updateKeyboardButtonsState(Z_button_state, sf::Keyboard::Z);
        updateKeyboardButtonsState(Ctrl_button_state, sf::Keyboard::LControl);
    }

    void EventService::processEvents()
    {
        if (isGameWindowOpen())
        {
            // Iterate over all events in the queue.
            while (game_window->pollEvent(game_event))
            {
                if (gameWindowWasClosed() || hasQuitGame())
                    game_window->close();
            }
        }
    }

    void EventService::updateButtonsState(ButtonState& button_state)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            switch (button_state)
            {
            case ButtonState::RELEASED:
                button_state = ButtonState::PRESSED;
                break;
            case ButtonState::PRESSED:
                button_state = ButtonState::HELD;
                break;
            }
        }
        else
        {
            button_state = ButtonState::RELEASED;
        }
    }

    void EventService::updateKeyboardButtonsState(ButtonState& current_button_state, sf::Keyboard::Key keyboard_button)
    {
        if (sf::Keyboard::isKeyPressed(keyboard_button))
        {
            switch (current_button_state)
            {
            case ButtonState::RELEASED:
                current_button_state = ButtonState::PRESSED;
                break;
            case ButtonState::PRESSED:
                current_button_state = ButtonState::HELD;
                break;
            }
        }
        else
        {
            current_button_state = ButtonState::RELEASED;
        }
    }

    bool EventService::isGameWindowOpen() { return game_window != nullptr; }

    bool EventService::gameWindowWasClosed() { return game_event.type == sf::Event::Closed; }

    bool EventService::hasQuitGame() { return (isKeyboardEvent() && pressedEscapeKey()); }

    bool EventService::isKeyboardEvent() { return game_event.type == sf::Event::KeyPressed; }

    bool EventService::pressedEscapeKey() { return game_event.key.code == sf::Keyboard::Escape; }

    bool EventService::pressedLeftMouseButton() { return left_mouse_button_state == ButtonState::PRESSED; }

    bool EventService::pressedRightMouseButton() { return right_mouse_button_state == ButtonState::PRESSED; }

    void EventService::setLeftMouseButtonState(ButtonState button_state) { left_mouse_button_state = button_state; }

    bool EventService::pressedZKey() { return Z_button_state == ButtonState::PRESSED; }

    bool EventService::pressedCtrlKey() { return Ctrl_button_state == ButtonState::HELD; }
    
    bool EventService::isCtrlZPressed()
    {
        return pressedCtrlKey() && pressedZKey();
    }
}