#include "../../header/UI/Gameplay/GameplayUIController.h"
#include "../../header/Global/Config.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Gameplay/GameplayService.h"
#include "../../header/Sound/SoundService.h"
#include "../../header/Main/GameService.h"

namespace UI
{
    namespace GameplayUI
    {
        using namespace Main;
        using namespace Sound;
        using namespace UIElement;
        using namespace Global;

        GameplayUIController::GameplayUIController()
        {
            createButton();
            createTexts();
        }

        GameplayUIController::~GameplayUIController()
        {
            destroy();
        }

        void GameplayUIController::initialize()
        {
            initializeButton();
            initializeTexts();
        }

        void GameplayUIController::createButton()
        {
            menu_button = new ButtonView();
        }

        void GameplayUIController::createTexts()
        {
            score_text = new TextView();
            time_text = new TextView();
        }

        void GameplayUIController::initializeButton()
        {
            menu_button->initialize("Menu Button",
                Config::menu_button_large_texture_path,
                button_width, button_height,
                sf::Vector2f(menu_button_x_position, menu_button_y_position));

            registerButtonCallback();
        }

        void GameplayUIController::initializeTexts()
        {
            initializeScoreText();
            initializeTimeText();
        }

        void GameplayUIController::initializeScoreText()
        {
            score_text->initialize("Score  :  0", sf::Vector2f(score_text_x_position, text_y_position), FontType::ROBOTO, font_size);
        }

        void GameplayUIController::initializeTimeText()
        {
            time_text->initialize("00 : 00 : 00", sf::Vector2f(time_text_x_position, text_y_position), FontType::ROBOTO, font_size);
        }

        void GameplayUIController::update()
        {
            menu_button->update();
            updateScoreText();
            updateTimeText();
        }

        void GameplayUIController::render()
        {
            menu_button->render();
            score_text->render();
            time_text->render();
        }

        void GameplayUIController::show()
        {
            menu_button->show();
            score_text->show();
            time_text->show();
        }

        void GameplayUIController::updateScoreText()
        {
            int score = ServiceLocator::getInstance()->getGameplayService()->getScore();
            sf::String score_string = "Score  :  " + std::to_string(score);

            score_text->setText(score_string);
            score_text->update();
        }

        void GameplayUIController::updateTimeText()
        {
            float elapsed_time = ServiceLocator::getInstance()->getGameplayService()->getElapsedTime();

            int hours = static_cast<int>(elapsed_time) / 3600;
            int minutes = (static_cast<int>(elapsed_time) % 3600) / 60;
            int seconds = static_cast<int>(elapsed_time) % 60;

            sf::String elapsed_time_string =
                (hours < 10 ? "0" : "") + std::to_string(hours) + " : " +
                (minutes < 10 ? "0" : "") + std::to_string(minutes) + " : " +
                (seconds < 10 ? "0" : "") + std::to_string(seconds);

            time_text->setText(elapsed_time_string);
            time_text->update();
        }

        void GameplayUIController::menuButtonCallback()
        {
            ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
            GameService::setGameState(GameState::MAIN_MENU);
        }

        void GameplayUIController::registerButtonCallback()
        {
            menu_button->registerCallbackFuntion(std::bind(&GameplayUIController::menuButtonCallback, this));
        }

        void GameplayUIController::destroy()
        {
            delete (menu_button);
            delete (score_text);
            delete (time_text);
        }
    }
}