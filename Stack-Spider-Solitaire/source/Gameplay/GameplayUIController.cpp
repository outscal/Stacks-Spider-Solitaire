#include "../../header/Gameplay/GameplayUIController.h"
#include "../../header/Global/Config.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Gameplay/GameplayService.h"

namespace Gameplay
{
    using namespace UIElement;
    using namespace Global;

    GameplayUIController::GameplayUIController()
    {
        createTexts();
    }

    GameplayUIController::~GameplayUIController()
    {
        destroy();
    }

    void GameplayUIController::initialize()
    {
        initializeTexts();
    }

    void GameplayUIController::createTexts()
    {
        score_text = new TextView();
        time_text = new TextView();
    }

    void GameplayUIController::initializeTexts()
    {
        initializeScoreText();
        initializeTimeComplexityText();
    }

    void GameplayUIController::initializeScoreText()
    {
        score_text->initialize("Score : 0", sf::Vector2f(score_text_x_position, text_y_position), FontType::ROBOTO, font_size);
    }

    void GameplayUIController::initializeTimeComplexityText()
    {
        time_text->initialize("Time : 01:00", sf::Vector2f(time_text_x_position, text_y_position), FontType::ROBOTO, font_size);
    }

    void GameplayUIController::update()
    {
        updateScoreText();
        updateTimeComplexityText();
    }

    void GameplayUIController::render()
    {
        score_text->render();
        time_text->render();
    }

    void GameplayUIController::show()
    {
        score_text->show();
        time_text->show();
    }

    void GameplayUIController::updateScoreText()
    {
        score_text->update();
    }

    void GameplayUIController::updateTimeComplexityText()
    {
        time_text->update();
    }

    void GameplayUIController::destroy()
    {
        delete (score_text);
        delete (time_text);
    }
}