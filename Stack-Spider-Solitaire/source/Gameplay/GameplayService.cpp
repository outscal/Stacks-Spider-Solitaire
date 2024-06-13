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

	void GameplayService::startLevel()
	{
		level_controller->startLevel();
	}

	void GameplayService::populateCardPiles(IStack<CardController*>* temp_card_deck)
	{
		level_controller->populateCardPiles(temp_card_deck);
	}

	void GameplayService::processCardClick(CardController* card_to_process)
	{
		level_controller->processCardClick(card_to_process);
	}

	float GameplayService::getTotalCardSpacingWidth()
	{
		return level_controller->getTotalCardSpacingWidth();
	}

	int GameplayService::getNumberOfPlaystacks() 
	{
		return level_controller->getNumberOfPlaystacks();
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
}