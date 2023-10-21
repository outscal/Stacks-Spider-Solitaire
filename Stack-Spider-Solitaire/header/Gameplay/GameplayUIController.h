#pragma once
#include "../../header/UI/Interface/IUIController.h"
#include "../../header/UI/UIElement/TextView.h"

namespace Gameplay
{
	class GameplayUIController : public Interface::IUIController
	{
	private:
		// Constants:
		const float font_size = 40.f;

		const float text_y_position = 6.4f;
		const float score_text_x_position = 850.f;
		const float time_text_x_position = 1600.f;

		UIElement::TextView* score_text;
		UIElement::TextView* time_text;

		void createTexts();
		void initializeTexts();
		void initializeScoreText();
		void initializeTimeComplexityText();

		void updateScoreText();
		void updateTimeComplexityText();

		void destroy();

	public:
		GameplayUIController();
		~GameplayUIController();

		void initialize() override;
		void update() override;
		void render() override;
		void show() override;
	};
}