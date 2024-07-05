#pragma once
#include "../../header/Gameplay/LevelController.h"
#include "../../header/Card/CardController.h"

namespace Gameplay
{
	using namespace Card;

	class GameplayService
	{
	private:
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

		int getScore();
		float getElapsedTime();

		void processCard(CardController* card_to_process);

	};
}