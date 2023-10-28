#pragma once
#include "Main/GraphicService.h"
#include "Event/EventService.h"
#include "UI/UIService.h"
#include "Sound/SoundService.h"
#include "Gameplay/GameplayService.h"
#include "Card/CardService.h"
#include "Global/TimeService.h"

namespace Global
{
    class ServiceLocator
    {
    private:
        Event::EventService* event_service;
        Main::GraphicService* graphic_service;
        Sound::SoundService* sound_service;
        UI::UIService* ui_service;
        Gameplay::GameplayService* gameplay_service;
        Card::CardService* card_service;
        Global::TimeService* time_service;

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
        Main::GraphicService* getGraphicService();
        Sound::SoundService* getSoundService();
        UI::UIService* getUIService();
        Gameplay::GameplayService* getGameplayService();
        Card::CardService* getCardService();
        Global::TimeService* getTimeService();
        void deleteServiceLocator();
    };
}