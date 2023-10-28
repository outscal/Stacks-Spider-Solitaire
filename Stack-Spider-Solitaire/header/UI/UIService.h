#pragma once
#include "UI/MainMenu/MainMenuUIController.h"
#include "UI/SplashScreen/SplashScreenUIController.h"
#include "Gameplay/GameplayUIController.h"
#include "UI/Interface/IUIController.h"

namespace UI
{
	class UIService
	{
	private:
		SplashScreen::SplashScreenUIController* splash_screen_ui_controller;
		MainMenu::MainMenuUIController* main_menu_ui_controller;
		Gameplay::GameplayUIController* gameplay_ui_controller;

		void createControllers();
		void initializeControllers();
		Interface::IUIController* getCurrentUIController();
		void destroy();

	public:
		UIService();
		~UIService();

		void initialize();
		void update();
		void render();
		void showScreen();
	};
}