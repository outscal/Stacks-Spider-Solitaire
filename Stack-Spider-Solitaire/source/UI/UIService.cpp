#include "../../header/UI/UIService.h"
#include "../../header/Main/GameService.h"
#include "../../header/UI/UIElement/TextView.h"

namespace UI
{
	using namespace Main;
	using namespace MainMenu;
	using namespace SplashScreen;
	using namespace GameplayUI;
	using namespace UIElement;
	using namespace Interface;
	using namespace Instructions;
	using namespace Credits;

	UIService::UIService()
	{
		splash_screen_ui_controller = nullptr;
		main_menu_ui_controller = nullptr;
		instructions_screen_ui_controller = nullptr;
		gameplay_ui_controller = nullptr;
		credit_screen_ui_controller = nullptr;

		createControllers();
	}

	void UIService::createControllers()
	{
		splash_screen_ui_controller = new SplashScreenUIController();
		main_menu_ui_controller = new MainMenuUIController();
		instructions_screen_ui_controller = new InstructionsScreenUIController();
		gameplay_ui_controller = new GameplayUIController();
		credit_screen_ui_controller = new CreditsScreenUIController();
	}

	UIService::~UIService()
	{
		destroy();
	}

	void UIService::initialize()
	{
		TextView::initializeTextView();
		initializeControllers();
	}

	void UIService::update()
	{
		IUIController* ui_controller = getCurrentUIController();
		if (ui_controller) ui_controller->update();
	}

	void UIService::render()
	{
		IUIController* ui_controller = getCurrentUIController();
		if (ui_controller) ui_controller->render();
	}

	void UIService::showScreen()
	{
		IUIController* ui_controller = getCurrentUIController();
		if (ui_controller) ui_controller->show();
	}

	void UIService::initializeControllers()
	{
		splash_screen_ui_controller->initialize();
		main_menu_ui_controller->initialize();
		instructions_screen_ui_controller->initialize();
		gameplay_ui_controller->initialize();
		credit_screen_ui_controller->initialize();
	}

	IUIController* UIService::getCurrentUIController()
	{
		switch (GameService::getGameState())
		{
		case GameState::SPLASH_SCREEN:
			return splash_screen_ui_controller;

		case GameState::MAIN_MENU:
			return main_menu_ui_controller;

		case GameState::INSTRUCTIONS:
			return instructions_screen_ui_controller;

		case GameState::GAMEPLAY:
			return gameplay_ui_controller;

		case GameState::CREDITS:
			return credit_screen_ui_controller;

		default:
			return nullptr;
		}
	}

	void UIService::destroy()
	{
		delete(splash_screen_ui_controller);
		delete(main_menu_ui_controller);
		delete(instructions_screen_ui_controller);
		delete(gameplay_ui_controller);
		delete(credit_screen_ui_controller);
	}
}