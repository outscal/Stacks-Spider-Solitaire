#include "Gameplay/GameplayService.h"

namespace Gameplay
{
	using namespace Card;

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

	void GameplayService::startLevel()
	{
		level_controller->startLevel();
	}

	void GameplayService::setCardToProcessInput(CardController* selected_card_controller)
	{
		level_controller->setCardToProcessInput(selected_card_controller);
	}

	float GameplayService::getCardWidth()
	{
		return level_controller->getCardWidth();
	}

	float GameplayService::getCardHeight()
	{
		return level_controller->getCardHeight();
	}

	float GameplayService::getElapsedTime()
	{
		return level_controller->getElapsedTime();
	}

	int GameplayService::getScore()
	{
		return level_controller->getScore();
	}

	void GameplayService::destroy()
	{
		delete (level_controller);
	}
} // namespace Gameplay