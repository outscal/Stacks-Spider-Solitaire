#pragma once
#include "../../header/Gameplay/GameplayService.h"
#include "../../header/Graphics/GraphicService.h"
#include "../../header/Event/EventService.h"
#include "../../header/Time/TimeService.h"
#include "../../header/UI/UIService.h"
#include "../../header/Sound/SoundService.h"
#include "../../header/Card/CardService.h"

namespace Global
{
    class ServiceLocator
    {
    private:
        Event::EventService* event_service;
        Graphics::GraphicService* graphic_service;
        Sound::SoundService* sound_service;
        UI::UIService* ui_service;
        Gameplay::GameplayService* gameplay_service;
        Card::CardService* card_service;
        Time::TimeService* time_service;


        ServiceLocator();
        ~ServiceLocator();

        void createServices();
        void clearAllServices();

    public:
        static ServiceLocator* getInstance();

        void initialize();
        void update();
        void render();

        Event::EventService* getEventService();
        Graphics::GraphicService* getGraphicService();
        Sound::SoundService* getSoundService();
        UI::UIService* getUIService();
        Gameplay::GameplayService* getGameplayService();
        Card::CardService* getCardService();
        Time::TimeService* getTimeService();

    };
}