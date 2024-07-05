#include "../../header/UI/SplashScreen/SplashScreenUIController.h"
#include "../../header/Main/GameService.h"
#include "../../header/Graphics/GraphicService.h"
#include "../../header/Sound/SoundService.h"
#include "../../header/Global/Config.h"
#include "../../header/Global/ServiceLocator.h"

namespace UI
{
    namespace SplashScreen
    {
        using namespace Main;
        using namespace Global;
        using namespace UIElement;
        using namespace Sound;
        using namespace Graphics;

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
            //ServiceLocator::getInstance()->getSoundService()->playBackgroundMusic();
            GameService::setGameState(GameState::MAIN_MENU);
        }

        sf::Vector2f SplashScreenUIController::getLogoPosition()
        {
            GraphicService* graphic_service = ServiceLocator::getInstance()->getGraphicService();

            float x_position = (graphic_service->getReferenceResolution().x - logo_width) / 2.0f;
            float y_position = (graphic_service->getReferenceResolution().y - logo_height) / 2.0f;

            return sf::Vector2f(x_position, y_position);
        }

        void SplashScreenUIController::show()
        {
            outscal_logo_view->playAnimation(AnimationType::FADE_IN, logo_animation_duration, std::bind(&SplashScreenUIController::fadeInAnimationCallback, this));
        }
    }
}