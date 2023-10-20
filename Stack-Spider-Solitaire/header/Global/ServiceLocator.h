#pragma once
#include "../../header/Main/GraphicService.h"
#include "../../header/Event/EventService.h"
#include "../../header/UI/UIService.h"
#include "../../header/Sound/SoundService.h"

namespace Global
{
    class ServiceLocator
    {
    private:
        Event::EventService* event_service;
        Main::GraphicService* graphic_service;
        Sound::SoundService* sound_service;
        UI::UIService* ui_service;

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
        void deleteServiceLocator();
    };
}