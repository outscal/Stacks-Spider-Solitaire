#pragma once
#include "../../header/UI/Interface/IUIController.h"
#include "../../header/UI/UIElement/TextView.h"
#include "../../header/UI/UIElement/ButtonView.h"

namespace UI
{
	namespace GameplayUI
	{
		class GameplayUIController : public Interface::IUIController
		{
		private:
			// Constants:
			const float font_size = 36.f;

			const float text_y_position = 11.f;
			const float score_text_x_position = 860.f;
			const float time_text_x_position = 1660.f;

			const float menu_button_x_position = 60.f;
			const float menu_button_y_position = 11.f;

			const float button_width = 100.f;
			const float button_height = 50.f;

			UIElement::TextView* score_text;
			UIElement::TextView* time_text;
			UIElement::ButtonView* menu_button;

			void createButton();
			void createTexts();
			void initializeButton();
			void initializeTexts();
			void initializeScoreText();
			void initializeTimeText();

			void updateScoreText();
			void updateTimeText();
			void menuButtonCallback();
			void registerButtonCallback();

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
}