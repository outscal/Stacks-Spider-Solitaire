#pragma once

class EventService;
class GraphicService;
class SoundService;
class UIService;

class ServiceLocator
{
private:
    EventService* event_service;
    GraphicService* graphic_service;
    SoundService* sound_service;
    UIService* ui_service;

    ServiceLocator();
    ~ServiceLocator();

    void createServices();
    void clearAllServices();

public:
    static ServiceLocator* getInstance();

    void initialize();
    void update();
    void render();

    EventService* getEventService();
    GraphicService* getGraphicService();
    SoundService* getSoundService();
    UIService* getUIService();
    void deleteServiceLocator();
};