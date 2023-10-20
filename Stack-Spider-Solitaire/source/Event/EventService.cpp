#include "../../header/Event/EventService.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Main/GraphicService.h"
#include <iostream>

namespace Event
{
    using namespace Global;
    using namespace Main;

    EventService::EventService() { game_window = nullptr; }

    EventService::~EventService() = default;

    void EventService::initialize()
    {
        game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();
    }

    void EventService::update()
    {
        updateButtonsState();
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

    void EventService::updateButtonsState()
    {
        updateLeftMouseButtonState();
        updateRightMouseButtonState();
    }

    void EventService::updateLeftMouseButtonState()
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            switch (left_mouse_button_state)
            {
            case ButtonState::RELEASED:
                left_mouse_button_state = ButtonState::PRESSED;
                break;
            case ButtonState::PRESSED:
                left_mouse_button_state = ButtonState::HELD;
                break;
            }
        }
        else
        {
            left_mouse_button_state = ButtonState::RELEASED;
        }
    }

    void EventService::updateRightMouseButtonState()
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            switch (right_mouse_button_state)
            {
            case ButtonState::RELEASED:
                right_mouse_button_state = ButtonState::PRESSED;
                break;
            case ButtonState::PRESSED:
                right_mouse_button_state = ButtonState::HELD;
                break;
            }
        }
        else
        {
            right_mouse_button_state = ButtonState::RELEASED;
        }
    }

    bool EventService::isGameWindowOpen() { return game_window != nullptr; }

    bool EventService::gameWindowWasClosed() { return game_event.type == sf::Event::Closed; }

    bool EventService::hasQuitGame() { return (isKeyboardEvent() && pressedEscapeKey()); }

    bool EventService::isKeyboardEvent() { return game_event.type == sf::Event::KeyPressed; }

    bool EventService::pressedEscapeKey() { return game_event.key.code == sf::Keyboard::Escape; }

    bool EventService::pressedLeftMouseButton() { return left_mouse_button_state == ButtonState::PRESSED; }

    bool EventService::pressedRightMouseButton() { return right_mouse_button_state == ButtonState::PRESSED; }
}