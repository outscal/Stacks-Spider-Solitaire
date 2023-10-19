#pragma once
#include <SFML/Graphics.hpp>
#include "../header/IUIController.h"

class ImageView;
class ButtonView;

class MainMenuUIController : public IUIController
{
private:
	// Constants:
	const float button_width = 400.f;
	const float button_height = 140.f;

	const float play_button_y_position = 500.f;
	const float instructions_button_y_position = 700.f;
	const float quit_button_y_position = 900.f;

	const float background_alpha = 85.f;

	ImageView* background_image;

	ButtonView* play_button;
	ButtonView* instructions_button;
	ButtonView* quit_button;

	void createImage();
	void createButtons();
	void initializeBackgroundImage();
	void initializeButtons();
	void registerButtonCallback();

	void playButtonCallback();
	void instructionsButtonCallback();
	void quitButtonCallback();

	void destroy();

public:
	MainMenuUIController();
	~MainMenuUIController();

	void initialize() override;
	void update() override;
	void render() override;
	void show() override;
};