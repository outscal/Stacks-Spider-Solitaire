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

	void GameplayService::populateCardPiles(IStack<CardController*>* temp_card_deck)
	{
		level_controller->populateCardPiles(temp_card_deck);
	}

	float GameplayService::getTotalSpacingWidth()
	{
		return level_controller->getTotalSpacingWidth();
	}

	int GameplayService::getNumberOfPlaystacks() 
	{
		return level_controller->getNumberOfPlaystacks();
	}

	void GameplayService::destroy()
	{
		delete (level_controller);
	}
}