#pragma once
#include <SFML/Graphics.hpp>
#include "ServiceLocator.h"

enum class GameState
{
	BOOT,
	SPLASH_SCREEN,
	MAIN_MENU,
};

class GameService
{
private:
	static GameState current_state;
	ServiceLocator* service_locator;
	sf::RenderWindow* game_window;

	void initialize();
	void initializeVariables();
	void showSplashScreen();
	void destroy();

public:
	GameService();
	virtual ~GameService();

	void ignite();
	void update();
	void render();
	bool isRunning();

	static void setGameState(GameState new_state);
	static GameState getGameState();
};