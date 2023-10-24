#pragma once
#include "../../header/UI/Interface/IUIController.h"
#include "../../header/UI/UIElement/ImageView.h"
#include "../../header/UI/UIElement/ButtonView.h"
#include "../../header/UI/UIElement/TextView.h"

namespace Instructions
{
	class InstructionsScreenUIController : public Interface::IUIController
	{
	private:
		// Constants:
		const float button_width = 400.f;
		const float button_height = 140.f;

		const float menu_button_y_position = 800.f;
		const float background_alpha = 85.f;

		static const int number_of_instructions = 7;
		const float top_offset = 90.f;
		const float text_spacing = 95.f;
		const int font_size = 50;

		const sf::Color text_color = sf::Color::White;

		sf::String instructions[number_of_instructions] = { "Arrange the cards in descending order from 'King' to 'Ace' for both suits.",
															"Create eight stacks of 'Spades' and 'Hearts'.",
															"Click the 'Deal' button to add new cards.",
															"Click on a 'Card' to select it.",
															"Click on the 'Stack' where you want to move the selected card.",
															"You can move 'King' to 'Empty slot' only.",
															"If you successfully arrange all cards in both suits, you 'Win' the game." };

		UIElement::ImageView* background_image;
		UIElement::ButtonView* menu_button;

		std::vector<UIElement::TextView*> instructions_text_list;

		void createImage();
		void createButtons();
		void createText();
		void initializeBackgroundImage();
		void initializeButtons();
		void initializeTexts();
		void registerButtonCallback();
		float calculateLeftOffsetForButton();

		void menuButtonCallback();

		void destroy();

	public:
		InstructionsScreenUIController();
		~InstructionsScreenUIController();

		void initialize() override;
		void update() override;
		void render() override;
		void show() override;
	};
}