#include "../header/ServiceLocator.h"
#include "../header/EventService.h"
#include "../header/GraphicService.h"
#include "../header/SoundService.h"
#include "../header/UIService.h"

ServiceLocator::ServiceLocator()
{
	graphic_service = nullptr;
	event_service = nullptr;
	sound_service = nullptr;
	ui_service = nullptr;

	createServices();
}

ServiceLocator::~ServiceLocator() { clearAllServices(); }

void ServiceLocator::createServices()
{
	event_service = new EventService();
	graphic_service = new GraphicService();
	sound_service = new SoundService();
	ui_service = new UIService();
}

void ServiceLocator::initialize()
{
	graphic_service->initialize();
	sound_service->initialize();
	event_service->initialize();
	ui_service->initialize();
}

void ServiceLocator::update()
{
	event_service->update();
	ui_service->update();
	graphic_service->update();
}

void ServiceLocator::render()
{
	ui_service->render();
	graphic_service->render();
}

void ServiceLocator::clearAllServices()
{
	delete(ui_service);
	delete(graphic_service);
	delete(sound_service);
	delete(event_service);
}

ServiceLocator* ServiceLocator::getInstance()
{
	static ServiceLocator instance;
	return &instance;
}

EventService* ServiceLocator::getEventService() { return event_service; }

GraphicService* ServiceLocator::getGraphicService() { return graphic_service; }

SoundService* ServiceLocator::getSoundService() { return sound_service; }

UIService* ServiceLocator::getUIService() { return ui_service; }

void ServiceLocator::deleteServiceLocator() { delete(this); }