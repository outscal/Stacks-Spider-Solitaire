#pragma once
#include "../../header/Gameplay/LevelController.h"
#include "../Card/CardController.h"

namespace Gameplay
{
	using namespace Card;

	class GameplayService
	{
	private:
		GameplayService* gameplay_service;
		LevelController* level_controller;

		void createLevelController();
		void destroy();

	public:
		GameplayService();
		~GameplayService();

		void initialize();
		void update();
		void render();

		void populateCardPiles(IStack<CardController*>* temp_card_deck);
		float getTotalCardSpacingWidth();
		int getNumberOfPlaystacks();
	};
}