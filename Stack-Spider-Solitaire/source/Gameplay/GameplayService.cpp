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

	void GameplayService::createLevel()
	{
	}

	float GameplayService::getCardWidth()
	{
		return level_controller->getCardWidth();
	}

	float GameplayService::getCardHeight()
	{
		return level_controller->getCardHeight();
	}

	void GameplayService::destroy()
	{
		delete (level_controller);
	}
}