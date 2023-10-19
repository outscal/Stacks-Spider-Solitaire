#pragma once
#include "../header/IUIController.h"
#include <SFML/Graphics.hpp>

class AnimatedImageView;

class SplashScreenUIController : public IUIController
{
private:
	// Constants:
	const float logo_animation_duration = 2.0f;
	const float logo_width = 600.f;
	const float logo_height = 134.f;

	AnimatedImageView* outscal_logo_view;

	void initializeOutscalLogo();
	void fadeInAnimationCallback();
	void fadeOutAnimationCallback();
	sf::Vector2f getLogoPosition();

public:
	SplashScreenUIController();
	~SplashScreenUIController();

	void initialize() override;
	void update() override;
	void render() override;
	void show() override;
};