#include "../header/SplashScreenUIController.h"
#include "../header/GameService.h"
#include "../header/GraphicService.h"
#include "../header/SoundService.h"
#include "../header/AnimatedImageView.h"
#include "../header/Config.h"

SplashScreenUIController::SplashScreenUIController()
{
    outscal_logo_view = new AnimatedImageView();
}

SplashScreenUIController::~SplashScreenUIController()
{
    delete (outscal_logo_view);
}

void SplashScreenUIController::initialize()
{
    initializeOutscalLogo();
}

void SplashScreenUIController::update()
{
    outscal_logo_view->update();
}

void SplashScreenUIController::render()
{
    outscal_logo_view->render();
}

void SplashScreenUIController::initializeOutscalLogo()
{
    sf::Vector2f position = getLogoPosition();
    outscal_logo_view->initialize(Config::outscal_logo_texture_path, logo_width, logo_height, position);
}

void SplashScreenUIController::fadeInAnimationCallback()
{
    outscal_logo_view->playAnimation(AnimationType::FADE_OUT, logo_animation_duration, std::bind(&SplashScreenUIController::fadeOutAnimationCallback, this));
}

void SplashScreenUIController::fadeOutAnimationCallback()
{
    ServiceLocator::getInstance()->getSoundService()->playBackgroundMusic();
    GameService::setGameState(GameState::MAIN_MENU);
}

sf::Vector2f SplashScreenUIController::getLogoPosition()
{
    sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();

    float x_position = (game_window->getSize().x - logo_width) / 2.0f;
    float y_position = (game_window->getSize().y - logo_height) / 2.0f;

    return sf::Vector2f(x_position, y_position);
}

void SplashScreenUIController::show()
{
    outscal_logo_view->playAnimation(AnimationType::FADE_IN, logo_animation_duration, std::bind(&SplashScreenUIController::fadeInAnimationCallback, this));
}