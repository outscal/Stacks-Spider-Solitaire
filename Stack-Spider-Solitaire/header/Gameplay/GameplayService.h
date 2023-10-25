#pragma once
#include "../../header/Gameplay/LevelController.h"

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

		float getCardWidth();
		float getCardHeight();
	};
}