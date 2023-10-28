#pragma once
#include "Card/CardController.h"
#include "Gameplay/LevelController.h"

namespace Gameplay
{
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

		void startLevel();
		void setCardToProcessInput(Card::CardController* selected_card_controller);

		float getCardWidth();
		float getCardHeight();
		float getElapsedTime();
		int getScore();
	};
} // namespace Gameplay