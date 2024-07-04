#include "../../header/Gameplay/GameplayService.h"

namespace Gameplay
{
	GameplayService::GameplayService()
	{
		level_controller = nullptr;
		createLevelController();
	}

	GameplayService::~GameplayService()
	{
		destroy();
	}

	void GameplayService::createLevelController()
	{
		level_controller = new LevelController();
	}

	void GameplayService::initialize()
	{
		level_controller->initialize();
	}

	void GameplayService::update()
	{
		level_controller->update();
	}

	void GameplayService::render()
	{
		level_controller->render();
	}

	void GameplayService::processCard(CardController* card_to_process)
	{
		level_controller->processCard(card_to_process);
	}

	void GameplayService::destroy()
	{
		delete (level_controller);
	}
}